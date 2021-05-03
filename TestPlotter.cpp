
#include "gnuplot-iostream.h"
// include source code of specialized class
Gnuplot gp;

using namespace std;
void test()
{
	gp << "cd 'C:\\Users\\Vincent Joshua\\Documents\\AAAAA\\University\\Project\\Data'\n";
	gp << "set xdata time\n";
	gp << "set timefmt '%H:%M:%S'\n";
	gp << "set xrange ['00:59:16.027849':'01:11:46.941288']\n";
	gp << "set yrange [0:30]\n";
	gp << "plot 'partial_data.txt' using 2:3" << endl;

#ifdef _WIN32
	// For Windows, prompt for a keystroke before the Gnuplot object goes out of scope so that
	// 
	// the gnuplot window doesn't get closed.
	std::cout << "Press enter to exit." << std::endl;
	std::cin.get();
#endif
}

void testInputFromFile(CS_SensorNetworkData<BKLabSensorDataEntry>& test_network)
{
	ifstream ifs;
	string basedir = "C:\\Users\\Vincent Joshua\\Documents\\AAAAA\\University\\Project\\Data\\";

	string filename = "partial_data.txt";

	string fullFilename = basedir;
	fullFilename += filename;

	ifs.open(fullFilename);
	if (ifs.is_open())
	{
		// skip first line if any (not needed here)
		if (test_network.loadNetworkDataFromFile(ifs))
		{
			cout << endl << "Data Loaded. Summary:" << endl;
			test_network.printNetworkInfoToScreen();
		}
		else
			cout << "Loading from file failed" << endl;
	}
	ifs.close();

	cout << endl << "Done." << endl;
}

void testPrintFromFile(CS_SensorNetworkData<BKLabSensorDataEntry>& test_network)
{
	test_network.printNetwork();
}

void testPlotting(CS_SensorNetworkData<BKLabSensorDataEntry>& test_network)
{
	BKLabPlot plot_settings;
	int data_plot;
	string option;

	// Setting plot data
	data_plot = plot_settings.dataPlot();

	// BK specific plot info
	gp << test_network.setPlotSettings();
	//gp << test_network.setXrange(); // Can remove to plot entire data
	//gp << test_network.setYrange(); // Can remove to plot entire data
	gp << plot_settings.setLabel(data_plot);
	
	
	// Independent plot constants 
	gp << test_network.plotNetworkString(1,data_plot);
	gp << test_network.getDataString() << endl;

	cout << "Do you want to plot something else?" << endl;
	cout << "Y or N?" << endl;
	cin >> option;
	while (option == "Y" || option == "y")
	{
	replot:
		// Setting plot data
		data_plot = plot_settings.dataPlot();
		gp << endl;
		//gp << test_network.setXrange(); // Can remove to plot entire data
		//gp << test_network.setYrange(); // Can remove to plot entire data
		gp << plot_settings.setLabel(data_plot) << endl;

		// Independent plot constants 
		gp << test_network.plotNetworkString(1, data_plot);
		gp << test_network.getDataString() << endl;

		gp << "replot\n" << endl;

		cout << "Do you want to plot something else?" << endl;
		cout << "Y or N?" << endl;
		option = "";
		cin >> option;
	}
	
	cout << "Done plot" << endl;
}


void testBK()
{
	CS_SensorNetworkData<BKLabSensorDataEntry> test_network;
	testInputFromFile(test_network);
	//testOutputToFile(test_network);
	//testPrintFromFile(test_network);
	testPlotting(test_network);
}

void testBeachInputFromFile(CS_SensorNetworkData<BeachSensorDataEntry>& test_network)
{
	ifstream ifs;
	string basedir = "C:\\Users\\Vincent Joshua\\Documents\\AAAAA\\University\\Project\\Data\\";

	string filename = "beach_data.csv";

	string fullFilename = basedir;
	fullFilename += filename;

	ifs.open(fullFilename);
	if (ifs.is_open())
	{
		// skip first line if any (not needed here)
		if (test_network.loadNetworkDataFromFile(ifs))
		{
			cout << endl << "Data Loaded. Summary:" << endl;
			test_network.printNetworkInfoToScreen();
		}
		else
			cout << "Loading from file failed" << endl;
	}
	ifs.close();

	cout << endl << "Done." << endl;
}
void testBeachPlotting(CS_SensorNetworkData<BeachSensorDataEntry>& test_network)
{
	BeachPlot plot_settings;
	int data_plot;

	data_plot = plot_settings.dataPlot();

	gp << test_network.setPlotSettings();
	//gp << test_network.setXrange(); // Can be omitted
	//gp << test_network.setYrange(); // Can be omitted
	gp << plot_settings.setLabel(data_plot);

	gp << test_network.plotNetworkString(2, data_plot);
	gp << test_network.getDataString() << endl;
}
void testBeach()
{
	CS_SensorNetworkData<BeachSensorDataEntry> test_network;
	testBeachInputFromFile(test_network);
	testBeachPlotting(test_network);
}


int main()
{
	//test();
	//testBK();
	testBeach();
	cout << "TEST DONE" << endl;
}