#include<iostream>
#include<fstream> 
#include<cmath>
#include<cstring>
#include<cstdlib>
//#include<limits>
#include<queue>

using namespace std;

#define D 3
#define ranf() \
  ((double)rand()/(1.0+(double)RAND_MAX))
  
class Particle
{
  //double INFINITY = numeric_limits<double>::infinity();
  
  double x[D]; // (x,y) coordinates
  //double p[D]; // momentum
  double m; // inverse mass
  double v[D]; // velocity
  //double T; // kinetic energy
  double r; // radius of particle
  int count;
  
  public:
	bool operator== (const Particle& b)
	{
	bool pos_f=true;
	bool vel_f=true;
	for (int i=0;i<D;i++)
	{
		if (x[i]!=b.x[i]) pos_f=false;
		if (v[i]!=b.v[i]) vel_f=false;
	}
	return (pos_f & vel_f);
	}
	Particle(double* x, double* v, double m, double r)
	{
		for (int i=0; i<D; i++)
		{
			this->x[i]=x[i];
			this->v[i]=v[i];
		}
		this->m=m;
		this->r=r;
	};
	Particle(int N)
	{
		for (int i=0; i<D; i++)
		{
			x[i]=0.5*N;
			v[i]=ranf();
			r=0.1;
			m=0.5;
		}
	};
	Particle()
	{
	};
	void move(double dt)
	{
		for (int i=0; i<D; i++)
		{
			x[i] += v[i]*dt;
		}
	};
	void record(ofstream& f) 
	{	
		for (int i=0; i<D; i++)
		{
			f << x[i] << "\t";
		}
		for (int i=0; i<D; i++)
		{
			f << v[i] << "\t";
		}
		f << endl;
	};
	int get_count() const { return count; } ;
	double nct (Particle b)
	{
		Particle a = *this;
		if (a==b) return INFINITY;
		double dvdx=0;
		double dxdx=0;
		double dvdv=0;
		double dx[D],dv[D];
		for (int i=0; i<D; i++)
		{
			dx[i]=b.x[i]-a.x[i];
			dv[i]=b.v[i]-a.v[i];
			dvdx+=dx[i]*dv[i];
			dvdv+=dv[i]*dv[i];
			dxdx+=dx[i]*dx[i];
		}
        if (dvdx>0) return INFINITY;
        double sigma = a.r + b.r;
        double d = (dvdx*dvdx) - dvdv * (dxdx - sigma*sigma);
		if (d < 0) return INFINITY;
        return -(dvdx + sqrt(d))/dvdv;
	};
	void timeToHitWall(double* tw, int N)
	{
		int n=0;
		while (n<2*D)
		{
			if (v[n/2]>0) {
				tw[n/2+1]= (N - x[n/2] - r)/v[n/2]; 
				tw[n/2]=INFINITY;
				n+=2;
			}
			else if (v[n/2]<0) {
				tw[n/2]=(r - x[n/2])/v[n/2];
				tw[n/2+1]=INFINITY;
				n+=2;
			}
			else 
			{
				tw[n/2]=INFINITY;
				tw[n/2+1]=INFINITY;
				n+=2;
			}
		}
		
		/*
		double d=0.0;
		int l = n%2;
		if (l==0 & v[n/2]<0.0)
		{
			d = abs(a[n].x[n/2] - (a[j].x[n/2] - pow(-1.0,l)*a[j].a));
			double collision_time = distance/abs(a[j].v[n/2]);
			if (collision_time < dt) { 
				dt = collision_time;
				whichn = n;
				whichj = j;
			}
		}
		else if (l!=0 & v[n/2]>0.0)
		{
		
		}*/
		
	};
	void collide(Particle b)
	{
		double dvdx=0;
		double dx[D],dv[D];
		for (int i=0; i<D; i++)
		{
			dx[i]=b.x[i]-this->x[i];
			dv[i]=b.v[i]-this->v[i];
			dvdx+=dx[i]*dv[i];
		}
		double dst = this->r + b.r;   // distance between particle centers at collison

        // normal force F, and in x and y directions
        double F = 2 * this->m * b.m * dvdx / ((this->m + b.m)*dst);
        double fx[D];
		for (int i=0; i<D; i++)
		{
			fx[i]=F*dx[i]/dst;
			this->v[i]+=fx[i]/(this->m);
			b.v[i]-=fx[i]/b.m;
		}


        // update collision counts
        this->count++;
        b.count++;
	};
	void bounceoffwall(int n)
	{
		v[n/2]=-v[n/2];
		count++;
	};
	double kineticEnergy()
	{
		double E=0;
		for (int i=0;i<D;i++)
		{
			E+=0.5*m*v[i]*v[i];
		}
		return E;
	};
};

class Gas
{
	class Event	
	{
		double time;
		Particle a;
		Particle b;
		int n;
		int cA,cB;
		public:
			Event(double t, Particle a, Particle b, int k)
			{
				this->time=t;
				this->a=a;
				this->b=b;
				this->n=k;
				if (a!=NULL) cA=(*a).get_count();
				else cA=-1;
				if (b!=NULL) cB=(*b).get_count();
				else cB=-1;
			};
			bool operator<(const Event& e) const
			{
				return (this->time>e.time);
			};
			bool isValid() 
			{
				if (a!=NULL & (*a).get_count()!=cA) return false;
				if (b!=NULL & (*b).get_count()!=cB) return false;
				return true;
			};
			friend void simulate(ofstream&, double);
			friend class Gas;
	};
	priority_queue<Event> pq;
	double t;
	double hz;
	//Particle[] p;
	vector<Particle> p;	//array of particles
	int N; //number of particles
	
	void predict(Particle a, double limit)
	{
		if (&a==NULL) return;
		
		for (int i=0;i<N;i++)
		{
			double dt=a.nct(p[i]);
			if (t+dt<=limit) pq.push(Event(t+dt,&a,&p[i],2*D));
		}
		double dtw[2*D];
		a.timeToHitWall(dtw, N);
		for (int j=0;j<2*D;j++)
		{
			if (t+dtw[j]<=limit) pq.push(Event(t+dtw[j],&a,NULL,j));
		}
	};
	void write(ofstream& f, double limit)
	{
		for (int i=0;i<N;i++)
		{
			p[i].record(f);
		}
		if (t<limit) pq.push(Event(t+1.0/hz, NULL,NULL,0));
	};
	
	
	public:
		Gas(vector<Particle> particles, int N)
		{
			this->N=N;
			this->t=0;
			this->hz=0.5;
			this->p=particles;
		};
		void simulate(ofstream& f, double limit)
		{
			pq = priority_queue<Event>();
			for (int i=0; i<N; i++)
			{
				predict(p[i], limit);
			}
			pq.push(Event(0, NULL,NULL,0));
			
			while (!pq.empty())
			{
				Event e = pq.top();
				pq.pop();
				if (!e.isValid()) continue;
				Particle* a = e.a;
				Particle* b = e.b;
				for (int i=0; i<N; i++)	p[i].move(e.time-t);
				t=e.time;
				
				if (a!=NULL & b!=NULL) (*a).collide((*b));
				else if (a!=NULL & b==NULL) (*a).bounceoffwall(e.n);
				else if (a==NULL & b==NULL) write(f, limit);
				
				predict((*a),limit);
				predict((*b),limit);
			}
		};
		double kEnergy()
		{
			double E=0.0;
			for (int i=0; i<N; i++)
			{
				E+=p[i].kineticEnergy();
			}
			return E;
		};

};

int main()
{
	ofstream fout;
	fout.open("gas.dat");
	const int N = 1;
	vector<Particle> particles;
	for (int i=0;i<N;i++)
	{
		particles[i]=Particle(N);
	}
	Gas gas = Gas(particles, N);
	cout << "kin energy before " << gas.kEnergy() << endl;
	gas.simulate(fout, 2);
	cout << "kin energy after " << gas.kEnergy() << endl;
	fout.close();
}