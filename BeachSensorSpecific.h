#pragma once
#include "SensorDataBasicClasses.h"
#include "SensorData.h"

// Specialization of "date class" for BKLab sensor data: using inheritance
class BeachDate : public basicSensorDate {
protected: 
	;
public:
	virtual bool setFromString(const string &dateInputString, bool allowOverwrite = true)
	{// in string example: "2004-03-31" // bk lab
                            //"08/30/2013"
		string element; bool result;
		unsigned short int in_year; unsigned char in_month, in_day;
		element = dateInputString.substr(6, 4);
		in_year = stoul(element);
		if (in_year < 2014)
			return false;
		element = dateInputString.substr(0, 2);
		in_month = (unsigned char)stoul(element);
		element = dateInputString.substr(3, 2);
		in_day = (unsigned char)stoul(element);		
		result = setDate(in_year, in_month, in_day, allowOverwrite);	
		return result;
	}
};
// Specialization of "time class" for BeachLab sensor data: using inheritance
class BeachTime : public basicSensorTime {
protected:
	;
public:	
	virtual bool setFromString(const string& timeInputString, bool allowOverwrite = true)
	{// in string example: "03:38:15.757551" // bk lab
                            //"08:00:00 PM" 
		string element, format; bool result;
		unsigned char in_hour, in_minute; float in_second;
        element = timeInputString.substr(0, 2);
		in_hour = (unsigned char) stoul(element);
		element = timeInputString.substr(3, 2);
		in_minute = (unsigned char) stoul(element);
		element = timeInputString.substr(6, 2);// if too long, will be terminated at the end of the string
		in_second = stof(element);
        format = timeInputString.substr(9, 2);
        if(format=="PM" && in_hour<12) // Allows conversion of AM/PM to 24 hour
        {
            in_hour = in_hour+12;
        }
		result = setTime(in_hour, in_minute, in_second, allowOverwrite);
		return result;
	}
};
// Specialization of templated "date&time class" for BKLab sensor data: using Template specialization
///---------------- ///
// the BKLab Date-time : combination of the BKL-Date and BKL-Time
typedef sensorDateAndTime <BeachDate, BeachTime> BeachDateAndTime;
///---------------- ///
template <>
bool BeachDateAndTime::setFromString(const string& dateAndTimeInputString, bool allowOverwrite)
{	// in string example: "2004-03-31 03:38:15.757551 " 
							//"08/30/2013 08:00:00 PM,"
	string dateInputString, timeInputString;
	bool result_date, result_time;
	int length = dateAndTimeInputString.length();
	if (length < 23)
		return false;
	dateInputString = dateAndTimeInputString.substr(0, 11);
	timeInputString = dateAndTimeInputString.substr(11, 13);
	result_date = date.setFromString(dateInputString, allowOverwrite);
	result_time = time.setFromString(timeInputString, allowOverwrite);
	return (result_date && result_time);
}

typedef senDateTimeInterval <BeachDateAndTime> BeachInterval;

class BeachSensorFullReading : public basicSensorMultipleScalarReading {
protected:	
	static const int FULL_READING_SIZE = 6;
	static string shared_readingName_array[FULL_READING_SIZE];
	static string shared_readingUnit_array[FULL_READING_SIZE];
	static bool shared_nameInitialized_array[FULL_READING_SIZE];
	static bool shared_unitInitialized_array[FULL_READING_SIZE];
	// variable 0 is temparature (C); var 1 is Humidity (%); var 2 is light (?); var 3 is voltage (V)
	virtual bool blankInitialization()
	{
		//allocate memory (only once)
		if (!memIsAllocated)
			memAllocation();
		if (memIsAllocated)
		{
			// flags for values are all reset
			for (int i = 0; i < max_variables; i++)
				valueInitialized_array[i] = false;
			// names and units are shared by all instances via the static arrays (initialized only once)
		}		
		return memIsAllocated;
	}
	virtual bool memAllocation()
	{
		bool result = false;
		if (!memIsAllocated && max_variables > 0)
		{
			value_array = (float*)calloc(max_variables, sizeof(float));
			if (value_array == NULL)
				return false;
			//
			valueInitialized_array = (bool*)calloc(max_variables, sizeof(bool));
			if (valueInitialized_array == NULL)
				return false;
			
			// the following are shared by all instances
			nameInitialized_array = shared_nameInitialized_array;
			if (nameInitialized_array == NULL)
				return false;
			//
			unitInitialized_array = shared_unitInitialized_array;
			if (unitInitialized_array == NULL)
				return false;
			//
			readingName_array = shared_readingName_array;
			if (readingName_array == NULL)
				return false;
			//
			readingUnit_array = shared_readingUnit_array;
			if (readingUnit_array == NULL)
				return false;
			// finally set memory flag
			memIsAllocated = true;
			result = true;
		}
		return result;
	}
	virtual void memDeallocation()
	{
		if (memIsAllocated)
		{
			free(value_array);
			free(valueInitialized_array);			
			max_variables = 0;
			memIsAllocated = false;
		}
	}
	bool checkConsistencyOfInput(float in_temp, float in_turb, float in_depth, float in_height, float in_period, float in_battery)const
	{	// empirical, for the time being...
		if (in_temp>30)
			return false;
		if (in_turb>20 || in_turb<0)
			return false;
		if (in_depth<0)
			return false;
		if (in_height<0)
			return false;
		if (in_period<0)
			return false;
		if (in_battery<0)
			return false;
		return true;
	}
public:
	BeachSensorFullReading()
	{
		memIsAllocated = false;  max_variables = FULL_READING_SIZE;
		setnumOfVariables(max_variables);
	}
	~BeachSensorFullReading() { memDeallocation(); }
	BeachSensorFullReading(int numOfVariablesMeasured)
	{
		memIsAllocated = false;  max_variables = FULL_READING_SIZE;
		setnumOfVariables(max_variables);
	}
	// copy constructor
	BeachSensorFullReading(const BeachSensorFullReading& other)
	{
		memIsAllocated = false;  max_variables = 0;
		copyFrom(other, true);
	}
	BeachSensorFullReading(const basicSensorMultipleScalarReading& other)
	{
		memIsAllocated = false;  max_variables = 0;
		copyFrom(other, true);
	}
	// copy operators
	virtual void copyFrom(const BeachSensorFullReading& other, bool allowOverwrite = false)
	{
		// avoid self copy
		if (this != &other)
		{	// only copy from an initialized object to a not-initialized one
			if ((other.getInit()) && (!this->getInit() || allowOverwrite))
			{
				float otherVal; string otherString;int tot_val;
				int other_tot_val = other.getMaxVariables();
				// mem allocation
				if (!getMemIsAllocated())
					setnumOfVariables(other_tot_val);

				tot_val = getMaxVariables();

				for (int varnum = 0; varnum < tot_val; varnum++)
				{
					if (other.getVal(varnum, otherVal))
						setVal(varnum, otherVal, allowOverwrite);
				}
			}
		}
	}
	BeachSensorFullReading& operator = (const BeachSensorFullReading& other)
	{
		this->copyFrom(other, true);
		return*this;
	}
	virtual void copyFrom(const basicSensorMultipleScalarReading& other, bool allowOverwrite = false)
	{
		// avoid self copy
		if (this != &other)
		{	// only copy from an initialized object to a not-initialized one
			if ((other.getInit()) && (!this->getInit() || allowOverwrite))
			{
				float otherVal; string otherString, thisString; int tot_val = 0;
				int other_tot_val = other.getMaxVariables();
				// mem allocation
				if (!getMemIsAllocated())
					setnumOfVariables(other_tot_val);

				int this_tot_val = getMaxVariables();

				// scan all fields of the other object
				for (int varnum = 0; varnum < other_tot_val; varnum++)
				{
					// if the reading is initialized and the name is set
					if (other.getVal(varnum, otherVal) && other.getName(varnum, otherString))
					{
						// compare name (and unit) with all supported readings: if both match, set the value
						for (int this_varnum = 0; this_varnum < this_tot_val; this_varnum++)
						{	// compare name
							getName(this_varnum, thisString);
							if (otherString == thisString)
								if (other.getUnit(varnum, otherString))
								{	// compare unit: if this (too) matches, set the value
									getUnit(this_varnum, thisString);
									if (otherString == thisString)
									{
										setVal(this_varnum, otherVal, allowOverwrite); 
										tot_val++;
										if (tot_val == this_tot_val)
											return;
										break;
									}
								}								
						}
					}					
				}
			}
		}
	}
	BeachSensorFullReading& operator = (const basicSensorMultipleScalarReading& other)
	{
		this->copyFrom(other, true);
		return*this;
	}
	// setters
	virtual bool setName(int varnum, string inName, bool allowOverwrite = false)
	{
		cout << "Error: Attempt to overwrite Reading Name" << endl;
		return false;
	}
	virtual bool setUnit(int varnum, string inUnit, bool allowOverwrite = false)
	{
		cout << "Error: Attempt to overwrite Reading Unit" << endl;
		return false;
	}
	//
	virtual bool setnumOfVariables(int numOfVariablesMeasured){	return basicSensorMultipleScalarReading::setnumOfVariables(FULL_READING_SIZE);}
	//
	virtual void printClassInfo() const
	{
		string to_print;
		cout << "BeachSensorFullReading; memory allocated to support " << getMaxVariables() << " variables" << endl;
		for (int varnum = 0; varnum < getMaxVariables(); varnum++)
		{
			getName(varnum, to_print);
			cout << "Var " << varnum << " is " << to_print;
			getUnit(varnum, to_print);
			cout << " (" << to_print << ")" << endl;
		}
	}
	
	// getters/setters - specific of this class
	// getters - specific of this class
	virtual bool getTemp(float& outVal) const {return getVal(0, outVal);}
	virtual bool getTemp(float& outVal, string& outString) const { return getVal(0, outVal, outString); }
	virtual bool getTurb(float& outVal) const { return getVal(1, outVal); }
	virtual bool getTurb(float& outVal, string& outString) const { return getVal(1, outVal, outString); }
	virtual bool getTDepth(float& outVal) const { return getVal(2, outVal); }
	virtual bool getTDepth(float& outVal, string& outString) const { return getVal(2, outVal, outString); }
	virtual bool getWHeight(float& outVal) const { return getVal(3, outVal); }
	virtual bool getWHeight(float& outVal, string& outString) const { return getVal(3, outVal, outString); }
	virtual bool getPeriod(float& outVal) const {return getVal(4, outVal);}
	virtual bool getPeriod(float& outVal, string& outString) const { return getVal(4, outVal, outString); }
	virtual bool getBattery(float& outVal) const {return getVal(5, outVal);}
	virtual bool getBattery(float& outVal, string& outString) const { return getVal(5, outVal, outString); }
	// setters - specific of this class
	virtual bool setTemp(float in_val, bool allowOverwrite = false) {return setVal(0, in_val, allowOverwrite);}
	virtual bool setTurb(float in_val, bool allowOverwrite = false) { return setVal(1, in_val, allowOverwrite); }
	virtual bool setTDepth(float in_val, bool allowOverwrite = false) { return setVal(2, in_val, allowOverwrite); }
	virtual bool setWHeight(float in_val, bool allowOverwrite = false) { return setVal(3, in_val, allowOverwrite); }
	virtual bool setPeriod(float in_val, bool allowOverwrite = false) { return setVal(4, in_val, allowOverwrite); }
	virtual bool setBattery(float in_val, bool allowOverwrite = false) { return setVal(5, in_val, allowOverwrite); }
	//
	// set content from a string (coming from text file)
	virtual bool setFromString(const string& readingsInputString, bool allowOverwrite = true)
	{	// temperature humidity light voltage : sample input string (from line)
		// 20.3,1.18,0.891,0.08,3,9.4
		string element; 
		bool result_temp, result_turb, result_TDepth, result_WHeight, result_Period, result_Battery;
		size_t len, match_pos, start_pos=0;
		float in_temp, in_turb, in_TDepth, in_WHeight, in_Period, in_Battery;
		
		// first check on basic length;
		len = readingsInputString.length();
		if (len < 15)
			return false;
		//
		match_pos = readingsInputString.find(',', start_pos);
		len = match_pos - start_pos + 1;
		if (len < 3)
			return false;
		element = readingsInputString.substr(start_pos, len);
		in_temp = stof(element);
		//
		start_pos = match_pos + 1;
		match_pos = readingsInputString.find(',', start_pos);
		len = match_pos - start_pos + 1;
		if (len < 3)
			return false;
		element = readingsInputString.substr(start_pos, len);
		in_turb = stof(element);
		//
		start_pos = match_pos + 1;
		match_pos = readingsInputString.find(',', start_pos);
		len = match_pos - start_pos + 1;
		if (len < 3)
			return false;
		element = readingsInputString.substr(start_pos, len);
		in_TDepth = stof(element);
		//
		start_pos = match_pos + 1;
		match_pos = readingsInputString.find(',', start_pos);
		len = match_pos - start_pos + 1;
		if (len < 3)
			return false;
		element = readingsInputString.substr(start_pos, len);
		in_WHeight = stof(element);
		//
		start_pos = match_pos + 1;
		match_pos = readingsInputString.find(',', start_pos);
		len = match_pos - start_pos + 1;
		if (len < 1)
			return false;
		element = readingsInputString.substr(start_pos, len);
		in_Period = (float)stof(element);
		//
		start_pos = match_pos + 1;
		len = readingsInputString.length() - start_pos + 1;
		if (len < 3)
			return false;
		element = readingsInputString.substr(start_pos, len);
		in_Battery = (float)stof(element);

		// perform a check to see if these are all valid entries from a "valid line".
		if (checkConsistencyOfInput(in_temp, in_turb, in_TDepth, in_WHeight, in_Period, in_Battery))
		{
			result_temp = setTemp(in_temp, allowOverwrite);
			result_turb = setTurb(in_turb, allowOverwrite);
			result_TDepth = setTDepth(in_TDepth, allowOverwrite);
			result_WHeight = setWHeight(in_WHeight, allowOverwrite);
			result_Period = setPeriod(in_Period, allowOverwrite);
			result_Battery = setBattery(in_Battery, allowOverwrite);
			return (result_temp && result_turb && result_TDepth && result_WHeight && result_Period && result_Battery);
		}
		else return false;
	}
};

// init the shared variables (won't be allowed to change)
string BeachSensorFullReading::shared_readingName_array[FULL_READING_SIZE] = { "Temperature" ,  "Turbidity" , "Transducer Depth", 
																			"Wave Height" , "Wave Period" , "Battery Life"};
string BeachSensorFullReading::shared_readingUnit_array[FULL_READING_SIZE] = { "C" ,  "FTU" , "m", "m" , "s" , "%" };
bool BeachSensorFullReading::shared_nameInitialized_array[FULL_READING_SIZE] = {true, true, true, true, true, true};
bool BeachSensorFullReading::shared_unitInitialized_array[FULL_READING_SIZE] = {true, true, true, true, true, true};
//
// Specialization of templated "Sensor data point" for BKLab sensor data: using Template specialization
// the BKLab SensorDataEntry : combination of the Beach-Date_Time, Readings and info
class BeachNodeInfo {
protected:
	string measurementID; // Measurement ID
	unsigned short epoch; 
	unsigned short totAveragedSamples;	
public:
	BeachNodeInfo()
	{
		epoch = 0;
		totAveragedSamples = 0;
	}
	BeachNodeInfo(const BeachNodeInfo& other)
	{
		copyFrom(other);
	}
	unsigned char convertBeachNodeID(string moteID_str) // Known sensors for network
	{
		unsigned char val=0;
		if(moteID_str=="Montrose Beach,")
		{
			val = 1;
		}
		else if(moteID_str=="Ohio Street Beach,")
		{
			val = 2;
		}
		else if(moteID_str=="Calumet Beach,")
		{
			val = 3;
		}
		else if(moteID_str=="Osterman Beach,")
		{
			val = 4;
		}
		else if(moteID_str=="63rd Street Beach,")
		{
			val = 5;
		}
		else if(moteID_str=="Rainbow Beach,")
		{
			val = 6;
		}

		return val;
	}
	void setMeasurementID(string measure_info)
	{
		measurementID = measure_info;
	}
	string getMeasurementID() const {return measurementID;}
	void copyFrom(const BeachNodeInfo& other)
	{
		if (this != &other)
		{
			epoch = other.getEpoch();
			totAveragedSamples = other.getTotAveragedSamples();	
		}
	}
	void setEpoch(unsigned short val) { epoch = val; }
	unsigned short getEpoch() const { return epoch; }
	unsigned short getTotAveragedSamples() const { return totAveragedSamples; }	
	BeachNodeInfo& operator = (const BeachNodeInfo& other)
	{
		this->copyFrom(other);
		return*this;
	}
};

//
class BeachPlot {
protected:
;
public:
	int dataPlot()
	{
		int input;
		int data_plot;
		cout << "Select Data to Plot" << endl;
		cout << "Temperature = 1" << endl;
		cout << "Turbidity = 2" << endl;
		cout << "Teansducer Depth = 3" << endl;
		cout << "Wave Height = 4" << endl;
		cout << "Wave Period = 5" << endl;
		cout << "Battery Life = 6" << endl;
		cin >> input;

		switch(input)
		{
			case 1:
				data_plot = 3;
				break;
			case 2:
				data_plot = 4;
				break;
			case 3:
				data_plot = 5;
				break;
			case 4:
				data_plot = 6;
				break;
			case 5:
				data_plot = 7;
				break;
			case 6:
				data_plot = 8;
				break;
		}
		return data_plot;
	}
	string setLabel(int data_plot)
	{
		string label_string;
		string title_string = "set title \"Berkeley Lab Temperature Plot\"\n";
		string xlabel_string = "set xlabel \"Date and Time\"\n";
		string ylabel_string = "set ylabel ";
		string ylabel_data[6] = {"\"Temperature\"\n","\"Turbidity\"\n","\"Transducer Depth\"\n","\"Wave Height\"\n","\"Wave Period\"\n","\"Battery Life\"\n"};

		switch(data_plot)
		{
			case 3:
				label_string = title_string + xlabel_string + ylabel_string + ylabel_data[0];
				break;
			case 4:
				label_string = title_string + xlabel_string + ylabel_string + ylabel_data[1];
				break;
			case 5:
				label_string = title_string + xlabel_string + ylabel_string + ylabel_data[2];
				break;
			case 6:
				label_string = title_string + xlabel_string + ylabel_string + ylabel_data[3];
				break;
			case 7:
				label_string = title_string + xlabel_string + ylabel_string + ylabel_data[4];
				break;
			case 8:
				label_string = title_string + xlabel_string + ylabel_string + ylabel_data[5];
				break;
		}

		return label_string;
	}
};
//
typedef SensorDataEntry <BeachDateAndTime, BeachSensorFullReading, BeachNodeInfo> BeachSensorDataEntry;

///---------------- ///
// Make compatible with strings
// conversion?
// " " = 0
// "Montrose Beach" = 1; etc
template <>
bool BeachSensorDataEntry::checkNodeID(unsigned char val) { return ((val > 0)?true:false); }

template <>
bool BeachSensorDataEntry::setFromString(const string& fullLineInputString, bool allowOverwrite)
{	// "Montrose Beach,08/30/2013 08:00:00 AM,20.3,1.18,0.891,0.08,3,9.4,MontroseBeach201308300800"
	BeachNodeInfo beach_node;
	string dateAndTimeInputString, readingsInputString, epoch_str, moteID_str;
	bool result_date_time, result_readings, result_nodeid;
	int length = fullLineInputString.length();
	int start_pos, match_pos, len; 
	string epoc; 
	unsigned char moteID;

	// MOTE ID - DATE & TIME - MEASUREMENTS - MEASUREMENT ID
	// find substring with mote location ID
	start_pos = 3; // skip space in location name
	match_pos = fullLineInputString.find(',', start_pos);
	start_pos = 0;
	len = match_pos - start_pos + 1;
	if (len < 13)
		return false;
	moteID_str = fullLineInputString.substr(start_pos, len);
	moteID = beach_node.convertBeachNodeID(moteID_str);
	result_nodeid = checkAndSetNodeID(moteID);
	//cout << moteID_str << endl; // yes

	// find substring with date and time
	start_pos = match_pos + 1;
	match_pos = fullLineInputString.find(',', start_pos);
	len = match_pos - start_pos + 1;
	if (len < 14)
		return false;
	dateAndTimeInputString = fullLineInputString.substr(start_pos, len);
	result_date_time = dateNtime.setFromString(dateAndTimeInputString, allowOverwrite);
	//cout << dateAndTimeInputString << endl; // yes 

	// substring reading 1
	start_pos = match_pos + 1;
	match_pos = fullLineInputString.find(',', start_pos);
	len = match_pos - start_pos + 1;
	if (len < 5)
		return false;
	readingsInputString = fullLineInputString.substr(start_pos, len);
	//result_readings = reading.setFromString(readingsInputString, allowOverwrite);
	//cout << readingsInputString << endl;

	// substring reading 2
	start_pos = match_pos + 1;
	match_pos = fullLineInputString.find(',', start_pos);
	len = match_pos - start_pos + 1;
	if (len < 5)
		return false;
	readingsInputString += fullLineInputString.substr(start_pos, len);
	//result_readings = reading.setFromString(readingsInputString, allowOverwrite);
	//cout << readingsInputString << endl;

	// substring reading 3
	start_pos = match_pos + 1;
	match_pos = fullLineInputString.find(',', start_pos);
	len = match_pos - start_pos + 1;
	if (len < 5)
		return false;
	readingsInputString += fullLineInputString.substr(start_pos, len);
	//result_readings = reading.setFromString(readingsInputString, allowOverwrite);
	//cout << readingsInputString << endl;

	// substring reading 4
	start_pos = match_pos + 1;
	match_pos = fullLineInputString.find(',', start_pos);
	len = match_pos - start_pos + 1;
	if (len < 5)
		return false;
	readingsInputString += fullLineInputString.substr(start_pos, len);
	//result_readings = reading.setFromString(readingsInputString, allowOverwrite);
	//cout << readingsInputString << endl;

	// substring reading 5
	start_pos = match_pos + 1;
	match_pos = fullLineInputString.find(',', start_pos);
	len = match_pos - start_pos + 1;
	if (len < 2)
		return false;
	readingsInputString += fullLineInputString.substr(start_pos, len);
	//result_readings = reading.setFromString(readingsInputString, allowOverwrite);
	//cout << readingsInputString << endl;

	// substring reading 6
	start_pos = match_pos + 1;
	match_pos = fullLineInputString.find(',', start_pos);
	len = match_pos - start_pos + 1;
	if (len < 1)
		return false;
	readingsInputString += fullLineInputString.substr(start_pos, len);
	result_readings = reading.setFromString(readingsInputString, allowOverwrite);
	//cout << readingsInputString << endl;
	
	// finish substring with measurement ID
	start_pos = match_pos + 1; 	
	len = length-1;
	if (len < 20)
		return false;
	epoch_str = fullLineInputString.substr(start_pos, len);
	epoc = epoch_str;
	info.setMeasurementID(epoc);
	//cout << epoch_str << endl;
	//

	return (result_nodeid && result_date_time && result_readings);
}
template <>
string BeachSensorDataEntry::convert2string(bool longform) const
{	// date time epoch moteid temperature humidity light voltage - in string example: 
	// "2004-02-28 00:59:16.02785 3 1 19.9884 37.0933 45.08 2.69964" 
	string str_date_and_time, str_reading, str_epoc, str_nodeId, str_all;
	// Node ID
	str_nodeId = to_string(getNodeID());
	str_all += str_nodeId;
	str_all += ' ';
	// Date and time
	if (dateNtime.getInit())
	{
		str_date_and_time = dateNtime.convert2string(longform);
		str_all += str_date_and_time;
		//str_all += ' ';
	}
	// Readings
	if (reading.getInit())
	{
		str_reading = reading.convert2string(longform);
		str_all += str_reading;
		str_all += ' ';
	}
	// Measurement ID
	str_epoc = info.getMeasurementID();
	str_all += str_epoc;

	return str_all;
}
// Specialization of templated "Sensor data list" for BKLab sensor data: using Template specialization
// the BKLab SensorDataEntry : combination of the BKL-Date_Time, Readings and info
typedef CS_SensorDataList <BeachSensorDataEntry> BeachSensorDataList;