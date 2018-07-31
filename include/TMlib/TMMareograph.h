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
	Mareograph() = default;
    Mareograph(double _latitude, double _longitude, int _stepTime, std::string _locationName);
    Mareograph(double _latitude, double _longitude, int _stepTime, std::wstring _locationName);
    explicit Mareograph(int _stepTime);
	virtual ~Mareograph() = default;

	//-----------------//
	/* getter methods */
	//----------------//

    double getLongitude() const noexcept;
    double getLatitude() const noexcept;
    double getMaxHeight() const noexcept;
    double getMinHeight() const noexcept;
	std::size_t  getIndexX() const noexcept;
	std::size_t  getIndexY() const noexcept;
    int getStepTime() const noexcept;
    int getStartTime() const noexcept;
    std::string getLocationNameASCII() const noexcept;
    std::wstring getLocationNameUTF8() const noexcept;
    double getHeight(int index) const noexcept;
    unsigned int getSizeHeights() const noexcept;

	//----------------//
	/* setter methods */
	//----------------//

    void setLongitude(double _longitude);
    void setLatitude(double _latitude);
    void setStepTime(int _stepTime);
    void setLocationName(std::string _locationName);
    void setLocationName(std::wstring _locationName);

    void setIndexX(double startX, double deltaX);

    void setIndexX(std::size_t  index);

    void setIndexY(double startY, double deltaY, int sizeY);

    void setIndexY(std::size_t  index);

	//----------------//
	/*  push  height  */
	//----------------//

    void pushHeight(double height);
	void pushHeightFromArray(double** eta) { heights.push_back(eta[indexX][indexY]); }

	//----------------//
	/* Wtite to file  */
	//----------------//

    static void writeToFile(std::string path,
                            const std::vector<Mareograph> &M,
                            bool writeHeights = true);

    void writeToFileMareograph(std::string path);

    std::string getStartTimeString(int t);

    void writeToParametersMareograph(const std::string &path,
                                     const std::vector<Mareograph> &M);

    static void writeToFile(std::wstring path,
                            const std::vector<Mareograph> &M,
                            bool writeHeights = true);

    static std::vector<Mareograph> readFromFile(std::string path,
        double startX, double startY,
        double deltaX, double deltaY, int sizeY, bool readHeights = false);

    static std::vector<Mareograph> readFromFile(std::wstring path,
                                                                  double startX, double startY,
                                                                  double deltaX, double deltaY,
                                                                  int sizeY, bool readHeights = false);


private:
	double longitude, latitude;
	std::size_t indexX, indexY;
	int stepTime, startTime;
	double maxHeight, minHeight;

    std::wstring locationNameUTF8;
    std::string locationNameASCII;
	std::vector <double> heights;
};
}
#endif
