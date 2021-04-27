#include "BerkleyLabSensorSpecific.h"
#include "BeachSensorSpecific.h"


void test_date()
{
	string to_print;
	basicSensorDate testDate, testDate2;
	unsigned short int in_year = 2021;
	unsigned char in_month = 3;
	unsigned char in_day = 2;

	testDate.setDate(in_year, in_month, in_day);
	to_print = testDate;
	cout << "testDate : " << to_print << endl;
	testDate2.setDate(in_year, in_month, in_day);
	to_print = testDate2;
	cout << "testDate2 : " << to_print << endl;
	if (testDate > testDate2)
		cout << "testDate > testDate2" << endl;
	if (testDate < testDate2)
		cout << "testDate < testDate2" << endl;
	if (testDate == testDate2)
		cout << "testDate == testDate2" << endl;

	cout << "Done." << endl;
}
void test_time()
{
	string to_print;
	
	basicSensorTime testTime, testTime2;
	float in_second = 10.1234567;
	unsigned char in_minute = 56;
	unsigned char in_hour = 21;
	bool format = false; // True == AM/PM time

	testTime.setTime(in_hour, in_minute, in_second, format);
	to_print = testTime;
	cout << to_print << endl;
	cout << "testTime : " << to_print << endl;
	testTime2.setTime(in_hour, in_minute, in_second, format);
	to_print = testTime2;
	cout << to_print << endl;
	cout << "testTime2 : " << to_print << endl;
	
	if (testTime > testTime2)
		cout << "testTime > testTime2" << endl;
	if (testTime < testTime2)
		cout << "testTime < testTime2" << endl;
	if (testTime == testTime2)
		cout << "testTime == testTime2" << endl;

	cout << "Done ." << endl << endl;
}
void test_date_time()
{
	//test_date();
	//test_time();
	string to_print;
	basicSensorDateAndTime testDate_Time;
	basicSensorDateAndTime testDate_Time2;
	unsigned short int in_year = 2021;
	unsigned char in_month = 3;
	unsigned char in_day = 2;
	float in_second = 10.1234567;
	unsigned char in_minute = 56;
	unsigned char in_hour = 21;
	bool format = false; // AM/PM = true
	
	// test var 1;
	testDate_Time.date.setDate(in_year, in_month, in_day);
	testDate_Time.time.setTime(in_hour, in_minute, in_second, format);
	to_print = testDate_Time;
	cout << "testDate_Time : " << to_print << endl;
	
	// test var 2;
	testDate_Time2.date.setDate(in_year, in_month, in_day);
	testDate_Time2.time.setTime(in_hour, in_minute, in_second, format);
	to_print = testDate_Time2;
	cout << "testDate_Time2 : " << to_print << endl;
	
	if (testDate_Time > testDate_Time2)
		cout << "testDate_Time > testDate_Time2" << endl;
	if (testDate_Time < testDate_Time2)
		cout << "testDate_Time < testDate_Time2" << endl;
	if (testDate_Time == testDate_Time2)
		cout << "testDate_Time == testDate_Time2" << endl;

	cout << "Done." << endl << endl;
}
void test_basic_reading_class()
{
	string to_print;
		
	basicSensorMultipleScalarReading testMultiReading, testMultiReading2;
	testMultiReading.printClassInfo();
	testMultiReading.setnumOfVariables(4);
	testMultiReading.printClassInfo();
	float in_temp = 15.1234567;
	string in_name = "Temperature";
	string in_unit = "C";
	float in_humid = 10.12;
	string in_h_name = "Humidity";
	string in_h_unit = "percent";
	testMultiReading.setVal(0, in_temp);
	testMultiReading.setName(0, in_name);
	testMultiReading.setUnit(0, in_unit);
	testMultiReading.setVal(1, in_humid);
	testMultiReading.setName(1, in_h_name);
	testMultiReading.setUnit(1, in_h_unit);
	to_print = testMultiReading.convert2string(true);
	cout << to_print << endl;

	testMultiReading2 = testMultiReading;
	to_print = testMultiReading2.convert2string(true);
	cout << to_print << endl;

	//SensorData <basicSensorDateAndTime, basicSensorMultipleScalarReading> testFullData;

	// copy each term.
	//testFullData.printAll();
	cout << "Done." << endl << endl;
}
void test_BKLab_reading_class()
{
	string to_print; 
	BKLabSensorFullReading testBKLReading, testBKLReading2;
	testBKLReading.printClassInfo();
	float in_temp = 25.1234567;
	float in_humid = 32.12;
	float in_light = 45.0;
	float in_volt = 2.2;

	BKLabSensorFullReading test;
	string testLineSegment = "19.9884 37.0933 45.08 2.69964";
	if (test.setFromString(testLineSegment))
		cout << "Reading set as: " << test.convert2string(false) << endl;
	else
		cout << "Reading not set" << endl;
	cout << "Done" << endl;


	testBKLReading.setTemp(in_temp);
	testBKLReading.setHum(in_humid);
	testBKLReading.setLight(in_light);
	testBKLReading.setVolt(in_volt);

	to_print = testBKLReading.convert2string(true);
	cout << to_print << endl;
	
	cout << "Done." << endl << endl;
}
void test_BKLab_date_class()
{
	BKLabDate test;
	string testLineSegment = "2004-03-31 ";
	if(test.setFromString(testLineSegment))
		cout << "Date set as: " << test.convert2string(false) <<endl;
	else
		cout << "Date not set" << endl;

	cout << "Done" << endl;
}
void test_BKLab_time_class()
{
	BKLabTime test;
	string testLineSegment = "03:38:15.757551 AM";
	if (test.setFromString(testLineSegment))
		cout << "Time set as: " << test.convert2string(false) << endl;
	else
		cout << "Time not set" << endl;

	cout << "Done" << endl;
}
void test_BKLab_Date_and_time_class()
{
	BKLabDateAndTime test;
	string testLineSegment = "2004-03-31 03:38:15.757551 ";
	if (test.setFromString(testLineSegment))
		cout << "Time and Date set as: " << test.convert2string(false) << endl;
	else
		cout << "Time and Date not set" << endl;

	cout << "Done" << endl;
}
void test_BKLab_sensor_data()
{
	BKLabSensorDataEntry test;
	string testLineSegment = "2004-02-28 00:59:16.02785 3 1 19.9884 37.0933 45.08 2.69964";
	cout << "Test line is" << endl << testLineSegment << endl;
	if (test.setFromString(testLineSegment))
		cout << "Sensor entry set as:"<< endl << test.convert2string(false) << endl;
	else
		cout << "Sensor entry not set" << endl;

	cout << "Done" << endl;
}
void test_BKLab_dataList_item_insertion(BKLabSensorDataList& test_list, const string &testLineSegment)
{
	BKLabSensorDataEntry test;
	if (test.setFromString(testLineSegment))
	{
		cout << "Insertion to the list. Result: " << endl;
		if (test_list.addToList(test))
			test_list.printToScreen(false); //cout << "succeeded" << endl;
		else
			cout << "Insertion Failed" << endl;
	}
	else
		cout << "Sensor entry not set" << endl;

	cout << endl << endl;
}
void test_BKLab_dataList()
{
	// below this point still work in progress ....
	BKLabSensorDataList test_list;
	static const int TOT_TESTS = 10;
	string testLineSegmentArray[TOT_TESTS];
	int node_id = 1;
	test_list.setUpList(node_id);
	int max_test_i = 0;
	
	//list<BKLabSensorDataEntry>::iterator test_ptr;
	//list<BKLabSensorDataEntry> dataList;
	//test_ptr = dataList.begin();

	testLineSegmentArray[max_test_i++] = "2004-02-28 01:03:16.33393 11 1 19.3024 38.4629 45.08 2.68742";
	testLineSegmentArray[max_test_i++] = "2004-02-28 01:06:46.778088 18 1 19.175 38.8379 45.08 2.69964";
	testLineSegmentArray[max_test_i++] = "2004-02-28 01:09:22.323858 23 1 19.1652 38.872 45.08 2.68742";
	testLineSegmentArray[max_test_i++] = "2004-02-28 01:08:45.992524 22 1 19.1456 38.9401 45.08 2.68742";	
	testLineSegmentArray[max_test_i++] = "2004-02-28 00:59:16.02785 3 1 19.9884 37.0933 45.08 2.69964";
	testLineSegmentArray[max_test_i++] = "2004-02-28 01:11:46.941288 28 1 19.1456 38.9401 45.08 2.69964";
	testLineSegmentArray[max_test_i++] = "2004-02-28 01:10:46.250524 26 1 19.1456 38.872 45.08 2.68742";
	testLineSegmentArray[max_test_i++] = "2004-02-28 01:10:16.6789 25 1 19.1456 38.8379 45.08 2.69964";


	for (int test_i = 0; test_i < max_test_i; test_i++)
		test_BKLab_dataList_item_insertion(test_list, testLineSegmentArray[test_i]);
	
	cout << endl << "Done. Printing entire list" << endl;
	test_list.printToScreen(false);

	// now remove:
	cout << endl << endl;
	BKLabSensorDataEntry testEntry;
	int in_pos = 5;
	cout << "Remove element position " << in_pos << ": ";
	if(test_list.getFromList(in_pos, testEntry, true))
		cout << "done. Element: " << testEntry.convert2string(false) << endl;
	else
		cout << "failed." << endl;

	cout <<endl << "Done. Printing entire list" << endl;
	test_list.printToScreen(false);


	cout << "Done" << endl;
}

void print_vec(const vector<int>& vec)
{
	for (auto x : vec) {
		std::cout << ' ' << x;
	}
	cout << '\n';
}
void test_vect()
{
	std::vector<int> vec;
	
	print_vec(vec);
	auto it = vec.begin();
	vec.insert(it, 200);
	it = vec.begin();
	vec.insert(it+1, 300);
	it = vec.begin();
	vec.insert(it + 2, 400);

	it = vec.begin();
	vec.insert(it + 4, 600);

	print_vec(vec);

	cout << "Done." << endl << endl;
}
void test_BKLabNetwork()
{
	CS_SensorNetworkData<BKLabSensorDataEntry> test_network;
	BKLabSensorDataEntry in_sns_dataEntry;
	string testLineSegment = "2004-02-28 00:59:16.02785 3 1 19.9884 37.0933 45.08 2.69964";
	in_sns_dataEntry.setFromString(testLineSegment);
	
	test_network.printNetworkInfoToScreen();	
	
	test_network.addDataToNetwork(in_sns_dataEntry);
	test_network.printNetworkInfoToScreen();
	cout << "Done" << endl;

	testLineSegment = "2004-02-28 01:06:46.778088 18 2 19.175 38.8379 45.08 2.69964";
	in_sns_dataEntry.setFromString(testLineSegment);
	test_network.addDataToNetwork(in_sns_dataEntry);
	test_network.printNetworkInfoToScreen();

	testLineSegment = "2004-02-28 01:09:46.109598 24 10 19.1652 38.8039 45.08 2.68742";
	in_sns_dataEntry.setFromString(testLineSegment);
	test_network.addDataToNetwork(in_sns_dataEntry);
	test_network.printNetworkInfoToScreen();


	testLineSegment = "2004-02-28 01:13:46.20 30 5 19.1358 38.9061 45.08 2.68742";
	in_sns_dataEntry.setFromString(testLineSegment);
	test_network.addDataToNetwork(in_sns_dataEntry);
	test_network.printNetworkInfoToScreen();

	testLineSegment = "2004-02-28 01:12:46.251377 30 1 19.1358 38.9061 45.08 2.68742";
	in_sns_dataEntry.setFromString(testLineSegment);
	test_network.addDataToNetwork(in_sns_dataEntry);
	test_network.printNetworkInfoToScreen();

	BKLabSensorDataEntry testEntry;
	unsigned char in_nodeID = 1;
	unsigned int in_pos = 0;
	
	cout << endl << endl;

	cout << "Remove element position " << in_pos << " from node " << (int)in_nodeID << ": ";
	if (test_network.getDataFromNetwork(in_nodeID, in_pos, testEntry, true))
		cout << "done. Element: " << testEntry.convert2string(false) << endl;
	else
		cout << "failed." << endl;


	test_network.printNetworkInfoToScreen();
	cout << endl << endl;

}
void testInputFromFile(CS_SensorNetworkData<BKLabSensorDataEntry>& test_network)
{
	ifstream ifs;
	string basedir = "C:\\Users\\Vincent Joshua\\Documents\\AAAAA\\University\\Project\\Data\\";
	
	string filename = "sampled_out.txt";
	
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
void testOutputToFile(CS_SensorNetworkData<BKLabSensorDataEntry>& test_network, bool remove = false)
{
	ofstream ofs;
	string basedir = "C:\\Users\\Vincent Joshua\\Documents\\AAAAA\\University\\Project\\Data\\";
	string filename = "data_out.txt";

	string fullFilename = basedir;
	fullFilename += filename;

	ofs.open(fullFilename);
	if (ofs.is_open())
	{
		// addfirst line if any (not needed here)
		if (test_network.storeNetworkDataToFile(ofs, remove))
		{
			cout << endl << "Data Stored." << endl;
			if (remove)
			{
				cout << endl << "Summary:" << endl;
				test_network.printNetworkInfoToScreen();
			}			
		}
		else
			cout << "Storing to file failed" << endl;
	}
	ofs.close();

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

	data_plot = plot_settings.dataPlot();

	cout << test_network.setPlotSettings();
	//cout << test_network.setXrange(); // Can be omitted
	//cout << test_network.setYrange(); // Can be omitted
	cout << plot_settings.setLabel(data_plot);

	cout << test_network.plotNetworkString(2,data_plot);
	//cout << test_network.getDataString() << endl;
}
void testInputOutputFromFile()
{
	CS_SensorNetworkData<BKLabSensorDataEntry> test_network;
	testInputFromFile(test_network);
	//testOutputToFile(test_network);
	//testPrintFromFile(test_network);
	testPlotting(test_network);
}

// Test New sensor data
void test_Beach_date_class()
{
	BeachDate test;
	string testLineSegment = "08/30/2013 ";
	if(test.setFromString(testLineSegment))
		cout << "Date set as: " << test.convert2string(false) <<endl;
	else
		cout << "Date not set" << endl;

	cout << "Done" << endl;
}
void test_Beach_time_class()
{
	BeachTime test;
	string testLineSegment = "08:00:00 PM";
	if (test.setFromString(testLineSegment))
		cout << "Time set as: " << test.convert2string(false) << endl;
	else
		cout << "Time not set" << endl;

	cout << "Done" << endl;
}
void test_Beach_Date_and_time_class()
{
	BeachDateAndTime test;
	string testLineSegment = "08/30/2013 08:00:00 AM,";
	if (test.setFromString(testLineSegment))
		cout << "Time and Date set as: " << test.convert2string(false) << endl;
	else
		cout << "Time and Date not set" << endl;

	cout << "Done" << endl;
}
void test_Beach_reading_class()
{
	string to_print; 
	BeachSensorFullReading testBeachReading, testBeachReading2;
	testBeachReading.printClassInfo();
	float in_temp = 20.3;
	float in_turb = 1.18;
	float in_TDepth = 0.891;
	float in_WHeight = 0.08;
	float in_Period = 3;
	float in_Battery = 9.4;

	BeachSensorFullReading test;
	string testLineSegment = "20.3,1.18,0.891,0.08,3,9.4";
	if (test.setFromString(testLineSegment)) // where does the problem come from????
		cout << "Reading set as: " << test.convert2string(false) << endl;
	else
		cout << "Reading not set" << endl;
	cout << "Done" << endl;

	testBeachReading.setTemp(in_temp);
	testBeachReading.setTurb(in_turb);
	testBeachReading.setTDepth(in_TDepth);
	testBeachReading.setWHeight(in_WHeight);
	testBeachReading.setPeriod(in_Period);
	testBeachReading.setBattery(in_Battery);

	to_print = testBeachReading.convert2string(true);
	cout << to_print << endl;

	cout << "Done." << endl << endl;
}
void test_Beach_sensor_data()
{
	BeachSensorDataEntry test;
	string testLineSegment = "Montrose Beach,08/30/2013 08:00:00 AM,20.3,1.18,0.891,0.08,3,9.4,MontroseBeach201308300800";
	cout << "Test line is" << endl << testLineSegment << endl;
	if (test.setFromString(testLineSegment))
		cout << "Sensor entry set as:"<< endl << test.convert2string(false) << endl;
	else{
		cout << "Sensor entry not set" << endl;
	}
	cout << "Done" << endl;
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

	cout << test_network.setPlotSettings();
	//cout << test_network.setXrange(); // Can be omitted
	//cout << test_network.setYrange(); // Can be omitted
	cout << plot_settings.setLabel(data_plot);

	cout << test_network.plotNetworkString(1,data_plot);
	cout << test_network.getDataString() << endl;
}
void testBeachInputOutputFromFile()
{
	CS_SensorNetworkData<BeachSensorDataEntry> test_network;
	
	testBeachInputFromFile(test_network);
	testBeachPlotting(test_network);
}
void test_intervals()
{
	string to_print;
	BKLabInterval testInterval;
	BKLabDateAndTime test_start, test_stop, test_point;
	test_start.date.setDate(2021, 3, 14);
	test_start.time.setTime(23, 44, 0, false);
	test_stop.date.setDate(2021, 4, 14);
	test_stop.time.setTime(15, 25, 0);

	testInterval.setStart(test_start);
	testInterval.setStop(test_stop);
	testInterval.setDuration(1, 0, 0, true);

	to_print = testInterval.convert2string();
	cout << "Test Interval = " << to_print << endl;

	cout << "Advance" << endl;
	testInterval.advanceByDuration();
	to_print = testInterval.convert2string();
	cout << "Test Interval = " << to_print << endl;
	
	test_point = testInterval.getStart();
	cout << "Start contained: ";
	if (testInterval.contains(test_point))
		cout << "Yes" << endl;
	else
		cout << "No" << endl;
	
	test_point = testInterval.getMiddle();
	cout << "Middle contained: ";
	if (testInterval.contains(test_point))
		cout << "Yes" << endl;
	else
		cout << "No" << endl;

	test_point = testInterval.getStop();
	cout << "Stop contained: ";
	if (testInterval.contains(test_point))
		cout << "Yes" << endl;
	else
		cout << "No" << endl;


	cout << "Done" << endl;
}

void testSample(CS_SensorNetworkData<BKLabSensorDataEntry>& test_network)
{
	string to_print;
	BKLabInterval testInterval;
	BKLabDateAndTime test_start, test_stop;

	//
	ofstream ofs;
	string basedir = "C:\\Users\\Vincent Joshua\\Documents\\AAAAA\\University\\Project\\Data\\";
	string filename = "sampled_out.txt";
	string fullFilename = basedir;
	fullFilename += filename;


	BKLabSensorDataEntry temp_data, network_data, sampled_data, checker;
	float reading,measurement,average;
	vector<vector<float>> temp_array;
	vector<float>sampled_array;
	bool valid_time;
	int place_holder;
	int counter;
	int list_pos = 0;

	ofs.open(fullFilename);

	for(int node_ID=0;node_ID<test_network.getNetworkSize();node_ID++)
	{
		test_start.date.setDate(2004, 2, 28, true);
		test_start.time.setTime(1, 0, 0, true);
		test_stop.date.setDate(2004, 2, 28, true);
		test_stop.time.setTime(2, 0, 0, true);

		testInterval.setStart(test_start,true);
		testInterval.setStop(test_stop);
		testInterval.setDuration(1, 0, 0, true); // 1 hour sampling duration*/
		
		if(test_network.returnDataListSize(node_ID) > 0)
		{		
			getSamples:

			for (;list_pos<test_network.returnDataListSize(1);)
			{
				test_network.getDataFromNetwork(node_ID,list_pos,temp_data);
				network_data = temp_data;

				if(network_data.reading.getMaxVariables()==4)
				{
					if(network_data.dateNtime > testInterval.getStart() && network_data.dateNtime < testInterval.getStop())
					{
						vector<float> sub;
						for(int var_num=0;var_num<temp_data.reading.getMaxVariables();var_num++)
						{
							if(network_data.reading.getVal(var_num,reading))
							{
								measurement = reading;
								sub.push_back(measurement);
							}
						}
						temp_array.push_back(sub);
						sub.clear();
						list_pos++;
					}
					else if (network_data.dateNtime < testInterval.getStart())
						list_pos++;
					
					else
						goto getAverages;
				}
				else
					list_pos++;
			}

			getAverages:
			int var=0;
			while(var<temp_array[0].size())
			{
				average = 0;
				for(int i=0;i<temp_array.size();i++)
				{
					average += temp_array[i][var];
				}
				average = average/temp_array.size();
				sampled_array.push_back(average);
				//cout << average << endl;
				var++;
			}
			temp_array.clear();
			
			counter++;
			//
			sampled_data.dateNtime = testInterval.getMiddle();
			for(int i=0;i<sampled_array.size();i++)
			{
				sampled_data.reading.setVal(i,sampled_array[i],true);
			}
			sampled_data.checkAndSetNodeID(node_ID);
			sampled_data.info.setEpoch(counter);
			ofs << sampled_data.convert2string(false) << endl;
			//
			if(network_data.dateNtime > testInterval.getStop())
			{
				testInterval.advanceByDuration();
				sampled_array.clear();
				goto getSamples;
			}

			cout << "Sampled node " << node_ID << " entries" << endl;		
		}
		else 
			cout << "Node ID: " << node_ID << " not set" << endl;

		//end: // Reset time intervals
			list_pos = 0;
			temp_array.clear();
			sampled_array.clear();
			counter = 0; // Resets for next node ID 
			testInterval.resetAll();	
	}
	ofs.close();



	cout << endl;
	cout << "DONE" << endl;
}

void testSampleFromFile()
{
	CS_SensorNetworkData<BKLabSensorDataEntry> test_network;
	testInputFromFile(test_network);
	testSample(test_network);
	//testPlotting(test_network);
}

int main()
{	
	//test_date(); // COMPLETE
	//test_time(); // COMPLETE
	//test_date_time(); // COMPLETE
	//test_basic_reading_class(); 

	// BK data ==================================================
	//test_BKLab_date_class(); // COMPLETE
	//test_BKLab_time_class(); // COMPLETE
	//test_BKLab_Date_and_time_class(); // COMPLETE
	//test_BKLab_reading_class();
	//test_BKLab_sensor_data(); // COMPLETE
	//test_BKLab_dataList(); // COMPLETE

	//test_vect();
	//print_vec();

	//test_BKLab_dataList();
	//test_BKLabNetwork();

	//testInputOutputFromFile();

	// Beach data ==================================================
	//test_Beach_date_class();
	//test_Beach_time_class();
	//test_Beach_Date_and_time_class();
	//test_Beach_reading_class();
	//test_Beach_sensor_data();
	//testBeachInputOutputFromFile();

	// Processing data ===========================================
	testSampleFromFile();
	//test_intervals();

 	cout << "TEST COMPLETE" << endl << endl;
}