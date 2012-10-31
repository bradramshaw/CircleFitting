// CircleFitting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	
		DataExtractor extractor("E:/Users/Brad/Documents/GitHub/CircleFitting/CircleFitting/circledat.dat");

		double ** data = extractor.getDataArray();
		
		int nLines = extractor.getNumberOfLines();

		double min_x = INFINITY;
		double max_x = -INFINITY;
		for(int i = 0; i < nLines; i++){
			if( data[i][1] < min_x){
				min_x = data[i][1];
			}
			if( data[i][1] > max_x){
				max_x = data[i][1];
			}
		}
		double min_y = INFINITY;
		double max_y = -INFINITY;
		for(int i = 0; i < nLines; i++){
			if( data[i][2] < min_y){
				min_y = data[i][2];
			}
			if( data[i][2] > max_y){
				max_y = data[i][2];
			}
		}
		
		complex<double> I(0,1);
		
		int nPoints = 100;
		double wave_num = 25;
		double decay = 1;
		double x_inc = (max_x - min_x)/nPoints;
		double y_inc = (max_y - min_y)/nPoints;

		complex<double> ** z_wave = new complex<double>*[nPoints];
		for(int i = 0; i < nPoints; i ++)
		{
			z_wave[i] = new complex<double>[nPoints];
			for(int j = 0; j < nPoints; j++)
			{
				z_wave[i][j] = complex<double>(0,0);

			}
		}		
		

		for(int i = 0; i < nPoints ; i ++){
			for(int j = 0; j < nPoints; j++){
				for(int k = 0; k < nLines; k++){
					complex<double>  xarg(min_x + ((double) i) * x_inc - data[k][1],0);
					complex<double> yarg(min_y + ((double) j) * y_inc - data[k][2],0);
					z_wave[i][j] += exp( I * wave_num * (pow(xarg,2) + pow(yarg,2)) - decay *(pow(xarg,2) + pow(yarg,2)) );
				}
				z_wave[i][j] = abs(z_wave[i][j]);
			}
		}

		//Exp[I k ((x - x0)^2 + (y - y0)^2) - d ((x - x0)^2 + (y - y0)^2)]

		std::ofstream out;
		out.open("output.dat");
		out.precision(15);
		for(int i = 0; i < nPoints; i ++){
			for(int j = 0; j< nPoints; j++){
				out<<real(z_wave[i][j])<<"\t";
			}
			out<<endl;
		}
		out.close();
	
	
	return 0;
}

