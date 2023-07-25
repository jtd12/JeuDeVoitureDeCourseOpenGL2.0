#include"particuleSystem.h"


float MAP(float au32_IN, float au32_INmin, float au32_INmax, float au32_OUTmin, float au32_OUTmax)
{
    return ((((au32_IN - au32_INmin)*(au32_OUTmax - au32_OUTmin))/(au32_INmax - au32_INmin)) + au32_OUTmin);
}


double randMToN(double M, double N)
{
    return M + (rand() / ( RAND_MAX / (N-M) ) ) ;  
}


double rand_normal(double mean, double stddev)
{//Box muller method
    static double n2 = 0.0;
    static int n2_cached = 0;
    if (!n2_cached)
    {
        double x, y, r;
        do
        {
            x = 2.0*rand()/RAND_MAX - 1;
            y = 2.0*rand()/RAND_MAX - 1;

            r = x*x + y*y;
        }
        while (r == 0.0 || r > 1.0);
        {
            double d = sqrt(-2.0*log(r)/r);
            double n1 = x*d;
            n2 = y*d;
            double result = n1*stddev + mean;
            n2_cached = 1;
            return result;
        }
    }
    else
    {
        n2_cached = 0;
        return n2*stddev + mean;
    }
}

particule::particule(float tmax)
{
	

	for( int i=0;i<n;i++)
{
	th=2*M_PI*randMToN(0.0,1.0);
	ra=sqrt(-2*log(randMToN(0.0,1.0)));
	x[i]=300+int(d*ra*cos(th));
	y[i]=300+int(d*ra*sin(th));
	dx[i]=int(randMToN(0,50));
	dy[i]=int(randMToN(0,5));
	ttl[i]=int(randMToN(0,tmax));
}

}


particule::~particule()
{
	
}



void particule::draw(float zpos,float tmax)
{


	for( int i=0;i<n;i++)
	{
		if(ttl[i]>0)
		{
			glEnable(GL_COLOR_MATERIAL);
			glPushMatrix();
			fillCorpsNoir(ttl[i],tmax);
			glTranslated(-20-x[i],10-y[i],zpos);
			glutSolidCube(4);
			glPopMatrix();
			glDisable(GL_COLOR_MATERIAL);
		}
		else
		{
			th=2*M_PI*randMToN(0.0,1.0);
			ra=sqrt(-2*log(randMToN(0.0,1.0)));
			x[i]=40-int(d*ra*cos(th));
			y[i]=20+int(d*ra*sin(th));
			dx[i]=int(randMToN(0,100));
			dy[i]=int(randMToN(0,5));
			ttl[i]=int(randMToN(0,tmax));
			
		}
	}
	int i;
	for(i=0;i<n;i++)
	{
		dy[i]-=g;
		x[i]+=dx[i];
		y[i]+=dy[i];
		ttl[i]--;
	
	}
}

void particule::fillCorpsNoir(int t,float tmax)
{
	int temp=int(19*float(t)/tmax);
	glColor3d(kelvinR[temp],kelvinG[temp],kelvinB[temp] );
}

int particule::getNumber()
{
	return n;
}

void particule::setNumber(int numb)
{
	n+=numb;
}

void particule::setNumberEgal(int numb)
{
	n=numb;
}


