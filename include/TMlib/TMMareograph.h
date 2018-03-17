#ifndef MAREOGRAPH_H
#define MAREOGRAPH_H
//#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

namespace TM {
class Mareograph
{
public:
	Mareograph();
    Mareograph(double _latitude, double _longitude, int _stepTime, std::string _locationName);
    Mareograph(double _latitude, double _longitude, int _stepTime, std::wstring _locationName);
    Mareograph(int _stepTime);
	virtual ~Mareograph();
	
	//-----------------//
	/* getter methods */
	//----------------//
	
    double getLongitude() const;
    double getLatitude() const;
    double getMaxHeight() const;
    double getMinHeight() const;
    int getIndexX() const;
    int getIndexY() const;
    int getStepTime() const;
    int getStartTime() const;
    std::string getLocationNameASCII() const;
    std::wstring getLocationNameUTF8() const;
    double getHeight(int index) const;
    unsigned int getSizeHeights() const;
	
	//----------------//
	/* setter methods */
	//----------------//
	
    void setLongitude(double _longitude);
    void setLatitude(double _latitude);
    void setStepTime(int _stepTime);
    void setLocationName(std::string _locationName);
    void setLocationName(std::wstring _locationName);

    void setIndexX(double startX, double deltaX);

    void setIndexX(int index);
	
    void setIndexY(double startY, double deltaY, int sizeY);

    void setIndexY(int index);

	//----------------//
	/*  push  height  */
	//----------------//
	
    void pushHeight(double height);
	void pushHeightFromArray(double** eta) { heights.push_back(eta[indexX][indexY]); }
	
	//----------------//
	/* Wtite to file  */
	//----------------//
	
    static void writeToFile(std::string path,
                            const std::shared_ptr<std::vector<Mareograph> > M,
                            bool writeHeights = true);

    void writeToFileMareograph(std::string path);

    std::string getStartTimeString(int t);

    void writeToParametersMareograph(std::string path,
                                     const std::shared_ptr<std::vector<Mareograph> > M);
		
    static void writeToFile(std::wstring path,
                            const std::shared_ptr<std::vector<Mareograph> > M,
                            bool writeHeights = true);

    static std::shared_ptr <std::vector<Mareograph>> readFromFile(std::string path,
        double startX, double startY,
        double deltaX, double deltaY, int sizeY, bool readHeights = false);
	
    static std::shared_ptr <std::vector<Mareograph>> readFromFile(std::wstring path,
                                                                  double startX, double startY,
                                                                  double deltaX, double deltaY,
                                                                  int sizeY, bool readHeights = false);


private:
	double longitude, latitude;
	int indexX, indexY;
	int stepTime, startTime;
	double maxHeight, minHeight;
	
    std::wstring locationNameUTF8;
    std::string locationNameASCII;
	std::vector <double> heights;
};
}
#endif
