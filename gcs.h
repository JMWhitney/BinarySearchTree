#ifndef _GCS_H_
#define _GCS_H_

// make NO CHANGES to this file

#include <ostream>

class GCS
{
public:
	GCS() : name{nullptr} {}				// default constructor
	GCS(char const * const name);			// constructor
	~GCS();									// destructor

	// deep copy support
	GCS(const GCS& source);					// copy constructor
	GCS& operator=(const GCS& data2);		// assignment operator overload

	char const * const getName() const { return name; }
	void setName(char const * const name);	// set name for this instance

private:
	char* name;

	friend std::ostream& operator<<(std::ostream& out, const GCS& gcs);
	friend bool operator<(const GCS& gcs1, const GCS& gcs2);
	friend bool operator==(const GCS& gcs1, const GCS& gcs2);
};

#endif // _GCS_H_
