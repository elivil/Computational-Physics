#include<iostream>
#include<fstream> 
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<vector>
//#include<limits>
#include<queue>
#include<limits>
#include<cassert>
#include<ctime>
//#include <random>
//#include<array>

using namespace std;

#define D 3
#define ranf 1.0/RAND_MAX*rand 


 const double DMAX= numeric_limits<double>::max();
 const int NUMP = 100;
 const double eps=1E-6;
 
 /*const int seed1 = 10;
 const int seed2 = 5;*/

class Particle
{
  //double DMAX = numeric_limits<double>::infinity();
  
  
  
  public:
	  double x[D]; 
	  double p[D]; 
	  double m; 
	  double v[D]; 
	  double r; 
	  int count;
	  int index;
	  vector<double> tw;
	bool operator== (const Particle& b)
	{
	bool pos_f=true;
	bool vel_f=true;
	for (int i=0;i<D;i++)
	{
		if (x[i]!=b.x[i]) pos_f=false;
		if (v[i]!=b.v[i]) vel_f=false;
	}
	return ((pos_f & vel_f)&(m==b.m)&(r==b.r));
	}
	/*void v2p()
	{
		for (int i=0; i<D; i++)
		{
			p[i]=m*v[i];
		}
	};
	void p2v()
	{
		for (int i=0; i<D; i++)
		{
			v[i]=p[i]/m;
		}
	};*/
	Particle(double* pos, double* vel, double mass, double rad, int k)
	{
		m=mass;
		r=rad;
		index=k;
		for (int i=0; i<D; i++)
		{
			x[i]=pos[i];
			v[i]=vel[i];
			p[i]=vel[i]*m;
			
		}
		
	};
	Particle(bool w, double rad)
	{
		for (int i=0; i<D; i++)
		{
			x[i]=0;
			v[i]=0;
			p[i]=0;
		}
		m=0;
		r=rad;
		index=-1;
	
	}
	Particle(int n)
	{
		index=n;
		r=0.01;
		m=0.5;
		
		for (int i=0; i<D; i++)
		{
			x[i]=ranf();
			v[i]=0.01*(ranf()-0.5);
			p[i]=m*v[i];
			
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
	};
	int get_count() const { return count; } ;
	double nct (Particle b)
	{
		Particle a = *this;
		
		if (a==b) return DMAX;
		double dvdx=0;
		double dxdx=0;
		double dvdv=0;
		double dx[D],dv[D];
		for (int i=0; i<D; i++)
		{
			dx[i]=b.x[i]-x[i];
			dv[i]=b.v[i]-v[i];
			dvdx+=dx[i]*dv[i];
			dvdv+=dv[i]*dv[i];
			dxdx+=dx[i]*dx[i];
		}
        if (dvdx>=0) return DMAX;
		
        double sigma = r + b.r;
        double d = (dvdx*dvdx) - dvdv * (dxdx - sigma*sigma);
		//if (dvdv<0) cout << "oops" << endl;
		if (d < 0) return DMAX;
        return -(dvdx + sqrt(d))/dvdv;
	};
	void timeToHitWall() 
	{
		int n=0;
		tw.clear();
		//double* tw = new double[2*D];
		while (n<2*D)
		{

			if (v[n/2]>0) {
				
				tw.push_back(DMAX);
				tw.push_back((1.0 - x[n/2] - r)/v[n/2]); 
				n+=2;
			}
			else 
			{
				if (v[n/2]<0) {
				tw.push_back((r - x[n/2])/v[n/2]);
				tw.push_back(DMAX);
				n+=2;
				}
				else 
				{
				tw.push_back(DMAX);
				tw.push_back(DMAX);
				n+=2;
				}
			}
		}
		
		
		//return tw;
	};
	vector<double>& get_tw()  { 
		timeToHitWall();
		return tw; 
	};
	
	void bounceoffwall(int whichw)
	{
		//cout << "wall!" << endl;
		if (whichw%2==0)
		{
			if (v[whichw/2]<0) {
				v[whichw/2]=-v[whichw/2];}
				
		}
		else
		{
			if (v[whichw/2]>0) { v[whichw/2]=-v[whichw/2]; }
			
		}
			

		count++;
	};
	double kineticEnergy()
	{
		double T=0;
		for (int i=0;i<D;i++)
		{
			T+=0.5*m*v[i]*v[i];
		}
		return T;
	};
	friend class Gas;
};

void collide(Particle& a, Particle& b)
	{
		
		double dvdx=0;
		double dx[D],dv[D];
		for (int i=0; i<D; i++)
		{
			dx[i]=b.x[i]-a.x[i];
			dv[i]=b.v[i]-a.v[i];
			dvdx+=dx[i]*dv[i];
		}
		double dst = a.r + b.r;  

        
        double F = 2 * a.m * b.m * dvdx / ((a.m + b.m)*dst);
		
        double fx[D];
		for (int i=0; i<D; i++)
		{
			fx[i]=F*dx[i]/dst;
			a.v[i]+=fx[i]/(a.m);
			b.v[i]-=fx[i]/b.m;
		}
		
		//a.p2v();
		//b.p2v();

        a.count++;
        b.count++;
		//cout<<"bump!" << endl;
	};



class Gas
{
	class Event	
	{
		double time;
		Particle a;
		Particle b;
		int num;
		int cA,cB;
		bool fl;
		Gas *g;
		public:
			void setgas (Gas &g)
			{
				this->g=&g;
			}
			Event(double t, Particle a1, Particle b1, int k, Gas &g)
			{
				time=t;
				a=a1;
				b=b1;
				num=k;
				if (a.r!=0) cA=a.get_count();
				else cA=-1;
				if (b.r!=0) cB=b.get_count();
				else cB=-1;
				setgas(g);
			};
			bool operator<(const Event& e) const
			{
				return (time>e.time);
			};
			bool isValid() 
			{
				//cout << (*g).p.size() << endl;
				//cout << a.index << endl;
				if (a.r!=0 && (*g).p.at(a.index).get_count()!=cA)
				{
					return false;
				}
				if (b.r!=0 & b.get_count()!=cB) return false;
				return true;
			};
			friend void simulate(ofstream&, double);
			friend class Gas;
		
	};	
	priority_queue<Event> pq;
	double t;
	double hz;
	//Particle[] p;
	vector<Particle> p;
	//int N; //number of particles
	
	void predict(Particle a, double limit)
	{
		if (a.r==0) return;
		
		for (vector<Particle>::iterator it=p.begin(); it!=p.end();++it)
		{
			
			double dt=a.nct(*it);
			if ((dt>eps && dt!=DMAX) && t+dt<=limit) 
			{
				pq.push(Event(t+dt,a,*it,2*D,*this));
				
			}
		}
		vector<double> dtw=a.get_tw();
		//int j=0;
		for (vector<double>::iterator it=dtw.begin(); it!=dtw.end();++it)
		{
			if (((*it)>eps && (*it)!=DMAX) && t+(*it)<=limit) 
			{
				Particle w(true,0.0);
				pq.push(Event(t+(*it),a,w,it-dtw.begin(),*this));
				
				
			//j++;
			}
		}
	};
	void write(ofstream& f, double limit)
	{
		f << t << "\t" << kEnergy() << "\t";
		for (vector<Particle>::iterator it=p.begin(); it!=p.end();++it)
		{
			(*it).record(f);
		}
		f << endl;
		if (t<limit) 
		{
			Particle w(true,0.0);
			pq.push(Event(t+1.0/hz, w,w,0,*this));
		}
	};
	
	
	public:
		Gas(vector<Particle> particles)
		{
			//N=N;
			t=0;
			hz=0.5;
			p=particles;
		};
		double kEnergy()
		{
			double E=0.0;
			for (vector<Particle>::iterator it=p.begin(); it!=p.end();++it)
			{
				E+=(*it).kineticEnergy();
			}
			return E;
		};
		void simulate(ofstream& f, double limit)
		{
			pq = priority_queue<Event>();
			
			for (vector<Particle>::iterator it=p.begin(); it!=p.end();++it)
			{
				predict(*it, limit);
			}
			Particle w(true,0.0);
			pq.push(Event(0, w,w,0,*this));
			
			while (!pq.empty())
			{
				Event e = pq.top();
				
				pq.pop();
				
				if (!e.isValid()) continue;
				Particle a = e.a;
				Particle b = e.b;
				for (vector<Particle>::iterator it=p.begin(); it!=p.end();++it)	(*it).move(e.time-t);
				a.move(e.time-t);
				b.move(e.time-t);
				t=e.time;
				
				
				//vector<Particle>::iterator it=p.begin();
				if (a.r!=0 & b.r!=0) 
				{
					collide(p.at(a.index), p.at(b.index));
					a.count++;
					b.count++;
				}
				else 
				{
					if (a.r!=0 & b.r==0) 
					{
						p.at(a.index).bounceoffwall(e.num);
						a.count++;
					}
					else if (a.r==0 & b.r==0) write(f, limit);
				}
				if (a.index>=0) predict(p.at(a.index),limit);
				if (b.index>=0) predict(p.at(b.index),limit);
			}
		};
		
	

};

int main()
{
	ofstream fout;
	fout.open("gas.dat");
	srand(time(NULL));
	//const int N = 2;
	vector<Particle> particles;
	/*default_random_engine generator1 (seed1);
	default_random_engine generator2 (seed2);
	uniform_real_distribution<double> dist1(-2,2);
	uniform_real_distribution<double> dist2(0.11,NUMP);*/
	for (int i=0;i<NUMP;i++)
	{
		particles.push_back(Particle(i));
	}
	/*double vec1[1];
	double vec2[1];
	for (int i=0;i<1;i++)
	{
		vec1[i]=0.05;
		vec2[i]=0.049;
	}
	particles.push_back(Particle(vec1,vec2,0.5,0.001,0));
	for (int i=0;i<1;i++)
	{
		vec1[i]=0.15;
		vec2[i]=-0.049;
	}
	particles.push_back(Particle(vec1,vec2,0.5,0.001,1));*/
	Gas gas = Gas(particles);
	
	gas.simulate(fout, 500);
	
	fout.close();
	
	return 0;
}