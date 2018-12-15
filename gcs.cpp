#include "gcs.h"
#include <cstring>
#include <iostream>
#include <iomanip>

using namespace std;

GCS::GCS(char const * const name) : name{new char[strlen(name) +1]}
{
	strcpy(this->name , name);
}

GCS::~GCS()
{
	if (name)
		delete [] name;
}

GCS& GCS::operator=(const GCS& gcs)
{
	setName(gcs.name);
	return *this;
}

GCS::GCS(const GCS& source)
{
	setName(source.name);
}

void GCS::setName(char const * const name)
{
	//Two conditions we need to worry about. The passed information is nullptr
	//and/or current instance name is nullptr. If passed name is nullptr 
	//we cannot do a deep copy. If instance name is nullptr we cannot delete 
	//current data.
	if (this->name) { 
		delete [] this->name;
	}
	if (!name) {
		this->name = nullptr;
	} else {
		this->name = new char[strlen(name) + 1];
		strcpy(this->name , name);
	}
}

bool operator<(const GCS& gcs1, const GCS& gcs2)
{
	if (strcmp(gcs1.name , gcs2.name) < 0) {
		return true;
	} else {
		return false;
	}
}

bool operator==(const GCS& gcs1, const GCS& gcs2)
{
	if (strcmp(gcs1.name , gcs2.name) == 0) {
		return true;
	} else {
		return false;
	}
}

ostream& operator<<(ostream& out, const GCS& gcs)
{
	out << gcs.name;
	return out;
}
