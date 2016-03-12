/*
 * EulerUtils.cpp
 *
 *  Created on: 13/12/2013
 *      Author: terentz
 */



#include "EulerUtils.hpp"
//#include "Prime.hpp"
#include <sys/time.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <iomanip>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <sstream>
#include <istream>
#include <cmath>
#include <set>
//#include <stringstream>

//#include <array>

//using namespace std;
using std::endl;
using std::cout;
using std::sqrt;
using boost::lexical_cast;
using boost::bad_lexical_cast;
using std::setprecision;
using std::ostringstream;
using std::string;
using std::vector;
using std::set;
using std::ifstream;
using std::fstream;
using std::stringstream;
using std::to_string;
using std::operator+;
using std::atoi;





/**************************************************************************
***************************************************************************
******************************  ARITHMETIC  *******************************
***************************************************************************
**************************************************************************/






/*************************************************************************
**************************************************************************
************************  CUSTOM DATA STRUCTURES  ************************
**************************************************************************
*************************************************************************/

/* class GridArr - a grid made of arrays */
EulerUtils::CustomData::GridArr::GridArr ( ) {}
EulerUtils::CustomData::GridArr::GridArr ( string filename ) {
	cout << ( this->populate( filename ) ? "File read successful :)" : "File read failed!" ) << endl;
}
EulerUtils::CustomData::GridArr::GridArr ( int w , int d ) {
	this->wd = w;
	this->dp = d;
}
EulerUtils::CustomData::GridArr::GridArr ( string filename, int w, int d ) {
// set depth and width
	this->wd = w;
	this->dp = d;

// init the grids
	initGrids(w,d);

// read the file and populate 'em!
	cout << ( this->populate( filename ) ? "File read successful :)" : "File read failed!" ) << endl;
}
EulerUtils::CustomData::GridArr::~GridArr() {
	// tidy up inner arrays
	for ( int y = 0 ; y < this->dp ; ++y ) {
		delete [] str_grid[y];
		delete [] int_grid[y];
		str_grid[y] = NULL;
		int_grid[y] = NULL;
	}
	// tidy up outer arrays
	delete [] str_grid;
	delete [] int_grid;
	str_grid = NULL;
	int_grid = NULL;
}
bool EulerUtils::CustomData::GridArr::populate ( string filename ) {
	// init's
	ifstream file;
	//unsigned int y=0, x=0;
	int y=0, x;
	// open the target file
	file.open(filename.c_str());
	if ( file.good() ) {
		// test line
		cout << "File open success :)" << endl;
		// iterate thru the lines in the file
		while ( ! file.eof() ) {
			// get a line
			string raw_line;
			getline( file , raw_line );
			// test lines
			cout << "Line read" << endl;
			EulerUtils::Strings::splitstring job( const_cast<char*>(raw_line.c_str()) );
			cout << "splitstring created" << endl;
			// split it
			const vector<string> line_items = job.split(' ');
			cout << "splitstring split" << endl;
			// iterate thru the words
			for ( x=0 ; x<(signed)line_items.size() ; ++x ) {
				// test
				cout << "(x,y) = (" << x << "," << y << ")" << endl;
				str_grid[y][x] = line_items[x];
				int_grid[y][x] = EulerUtils::Strings::strToInt(str_grid[y][x]);
			}
			y++;
		}
		file.close();
		return true;
	}
	return false;
}
void EulerUtils::CustomData::GridArr::print ( string name ) {
	cout << "Printing " << name << endl;
	// iterate thru the rows
	for ( int y = 0 ; y < ((signed)sizeof(str_grid) / (signed)sizeof(str_grid[0])) ; ++y )
	{
		cout << endl;
		// iterate thru the cells
		for ( int x = 0 ; x < ((signed)sizeof(str_grid[0]) / (signed)sizeof(str_grid[0][0])) ; ++x )
		{
			// print it out!!
			cout << ( x == 0 ? "" : " ") << str_grid[y][x];
		}
	}
	cout << endl;
}
// init grids
void EulerUtils::CustomData::GridArr::initGrids( int w , int d ) {
	this->initIntGrid(w,d);
	this->initStrGrid(w,d);
}
void EulerUtils::CustomData::GridArr::initIntGrid( int w , int d ) {
	this->int_grid = new int* [d];
	for ( int y=0; y<d ; y++ ) {
		int_grid[y] = new int[w];
	}
}
void EulerUtils::CustomData::GridArr::initStrGrid( int w , int d ) {
	this->str_grid = new string* [d];
	for ( int y=0; y<d ; y++ ) {
		str_grid[y] = new string[w];
	}
}
string ** EulerUtils::CustomData::GridArr::getStrGrid() {
	return this->str_grid;
}
int ** EulerUtils::CustomData::GridArr::getIntGrid() {
	// TODO check this after next build
	return this->int_grid;
//	return out;
//return const_cast<int**>(this->int_grid);
}
// get dimensions
const int EulerUtils::CustomData::GridArr::width() {
	//	return const_cast<int>(this->wd);
	const int out = this->wd;
	return out;
}
const int EulerUtils::CustomData::GridArr::depth() {
	//	return const_cast<int>(this->dp);
	const int out = this->dp;
	return out;
}
// get cell content
const int EulerUtils::CustomData::GridArr::intCellContent( int x , int y ) {
	//	return const_cast<int>(this->int_grid[y][x]);
	const int out = this->int_grid[y][x];
	return out;
}
/* class GridVec - a grid made of vectors */
EulerUtils::CustomData::GridVec::GridVec ( ) {}
EulerUtils::CustomData::GridVec::GridVec ( string filename ) {
	cout << ( this->populate( filename ) ? "File read successful :)" : "File read failed!" ) << endl;
}
EulerUtils::CustomData::GridVec::GridVec ( string filename, int w, int d ) : GridVec( filename ) {
	this->wd = w;
	this->dp = d;
	//GridVec( filename );
}
bool EulerUtils::CustomData::GridVec::populate ( string filename ) {
	// init's
	ifstream file;
	int y=0, x=0;
	// open the target file
	file.open(filename.c_str());
	if ( file.good() ) {
		// iterate thru the lines in the file
		while ( ! file.eof() ) {
			// get a line
			string raw_line;
			getline( file , raw_line );
			// split it
			EulerUtils::Strings::splitstring job( const_cast<char*>(raw_line.c_str()) );
			const vector<string> lineItems = job.split(' ');
			// iterate thru the words
			for ( x=0 ; x<lineItems.size() ; ++x ) {
				str_grid[y][x] = lineItems[x];
				int_grid[y][x] = EulerUtils::Strings::strToInt(str_grid[y][x]);
			}
			y++;
		}
		file.close();
		return true;
	}
	return false;
}
void EulerUtils::CustomData::GridVec::print ( string name ) {
	cout << "Printing " << name << endl;
	// iterate thru the rows
	for ( int y = 0 ; y < str_grid.size() ; ++y )
	{
		cout << endl;
		// iterate thru the cells
		for ( int x = 0 ; x < str_grid[0].size() ; ++x )
		{
			// print it out!!
			cout << ( x == 0 ? "" : " ") << str_grid[y][x];
		}
	}
	cout << endl;
}





/*************************************************************************
**************************************************************************
*******************************  DISPLAY  ********************************
**************************************************************************
*************************************************************************/

template<class TYPE>	// for 1-D array
void EulerUtils::Display::printArray ( string itemName, const TYPE data[] ) {
	int len = sizeof(data) / sizeof(data[0]) ;
	cout << "Printing " << itemName << endl;
	for ( int index=0 ; index<len ; index++ ) {
		cout << ( index == 0 ? "" : ", " ) << data[index] ;
	}
	cout << endl << endl;
}
template<class Container>
void EulerUtils::Display::printCollection ( string const& itemName, Container const& data ) {
    cout << "Printing " << itemName << "..." << endl;
    for ( auto i = data.begin() ; i < data.end() ; i++ ) {
        switch ( i ) {
            case data.begin():
                cout << "( " << *i << ", " ;
                break;

            case (data.end() - 1):
                cout << *i << " )" << endl ;
                break;

            default:
                cout << *i << ", " ;
                break;

        }
    }

}
// TODO can this be made into an extension of the first (1-D) functions
template<class TYPE>	// for 2-D array
void EulerUtils::Display::printGrid ( string itemName, const TYPE data[][20] ) {
	int depth = sizeof(data) / sizeof(data[0]) ;
	int width = sizeof(data[0]) / sizeof(data[0][0]) ;
	cout << "Printing " << itemName << endl;
	for ( int y=0 ; y<depth ; y++ ) {
		for ( int x=0 ; x<width ; x++ ) {
			cout << ( x == 0 ? "" : ", " ) << data[y][x] ;
		}
		cout << endl;
	}
	cout << endl << endl;
}
template <typename K, typename V>
void EulerUtils::Display::printMap ( string itemName, const map<K,V>& data ) {
	cout << "in printMap" << endl;
	cout << "Printing " << itemName << "..." << endl;
	for ( auto i = data.cbegin(); i != data.cend(); i++ )
        cout << i->first << ": " << i->second << endl;
    cout << endl;
}
void EulerUtils::Display::printMap ( string itemName, const map<long long, int>& data ) {
	cout << "in printMap" << endl;
	cout << "Printing " << itemName << "..." << endl;
	for ( auto i = data.cbegin(); i != data.cend(); i++ )
        cout << i->first << ": " << i->second << endl;
    cout << endl;
}
void EulerUtils::Display::printMap ( string itemName, const map<string, int>& data ) {
	cout << "in printMap" << endl;
	cout << "Printing " << itemName << "..." << endl;
	for ( auto i = data.cbegin(); i != data.cend(); i++ )
        cout << i->first << ": " << i->second << endl;
    cout << endl;
}

//void EulerUtils::Display::printSet ( string itemName, const set<V>& data ) {
//template <class Coll>
//void EulerUtils::Display::printSet ( string itemName, Coll& data ) {
//    typename Coll::iterator current = data.cbegin();
//    typename Coll::iterator terminator = data.cend();
//    while ( current < terminator ) {
//        cout << current << endl;
//        ++current;
//    }
//
//	cout << endl << "Printing " << itemName << "..." << endl;
//	for ( auto i = data.cbegin(); i != data.cend(); i++ ) {
//        cout << ( i == data.cbegin() ? "" : ", " ) << *i ;
//    }
//    cout << endl;
//}
void EulerUtils::Display::printSet ( string itemName, const set<unsigned int>& data ) {
	cout << endl << "Printing " << itemName << "..." << endl;
	for ( auto i = data.cbegin(); i != data.cend(); i++ ) {
        cout << ( i == data.cbegin() ? "" : ", " ) << *i ;
    }
    cout << endl;
}
void EulerUtils::Display::printSet ( string itemName, const set<long long>& data ) {
	cout << endl << "Printing " << itemName << "..." << endl;
	for ( auto i = data.cbegin(); i != data.cend(); i++ ) {
        cout << ( i == data.cbegin() ? "" : ", " ) << *i ;
    }
    cout << endl;
}
void EulerUtils::Display::printSet ( string itemName, const set<unsigned long long>& data ) {
	cout << endl << "Printing " << itemName << "..." << endl;
	for ( auto i = data.cbegin(); i != data.cend(); i++ ) {
        cout << ( i == data.cbegin() ? "" : ", " ) << *i ;
    }
    cout << endl;
}
// TODO can these first two be merged using more templating??
//template<typename T>	// for 1-D vector
//void EulerUtils::printVector ( string itemName, const vector<T>& data ) {
void EulerUtils::Display::printVector ( string itemName, const vector<long long>& data, bool down ) {
	cout << "in printVector" << endl;
	cout << "Printing " << itemName << "..." << endl;
	for ( auto i = data.begin(); i != data.end(); i++ )
        if ( !down )
            cout << ( i == data.begin() ? "" : ", " ) << *i ;
        else
            cout << *i << endl;
    cout << endl;
}
void EulerUtils::Display::printVector ( string itemName, const vector<int> data, bool down ) {
	cout << "in printVector" << endl;
	cout << "Printing " << itemName << "..." << endl;
	for ( auto i = data.begin(); i != data.end(); i++ )
        if ( !down )
            cout << ( i == data.begin() ? "" : ", " ) << *i ;
        else
            cout << *i << endl;
    cout << endl;
}
void EulerUtils::Display::printVector ( string itemName, const vector<unsigned int> data, bool down ) {
	cout << "in printVector" << endl;
	cout << "Printing " << itemName << "..." << endl;
	for ( auto i = data.begin(); i != data.end(); i++ )
        if ( !down )
            cout << ( i == data.begin() ? "" : ", " ) << *i ;
        else
            cout << *i << endl;
    cout << endl;
}
void EulerUtils::Display::printVector ( string itemName, const vector<string> data, bool down ) {
	cout << "in printVector" << endl;
	cout << "Printing " << itemName << "..." << endl;
	for ( auto i = data.begin(); i != data.end(); i++ )
        if ( !down )
            cout << ( i == data.begin() ? "" : ", " ) << *i ;
        else
            cout << *i << endl;
    cout << endl;
}





/*************************************************************************
**************************************************************************
****************************  NUMBER THEORY  *****************************
**************************************************************************
*************************************************************************/

long long EulerUtils::NumberTheory::Factorise::gcd( long long a, long long b ) {
    if ( b == 0 )
        return a;
    else
        return gcd(b, a%b);
}
set<unsigned long long> EulerUtils::NumberTheory::Factorise::integerDivisors( unsigned long long input, bool include_self ) {
	set<unsigned long long> output;
	output.insert(1);
	for ( long long testFactor = 2 ; testFactor <= input/2 ; testFactor++ )
		if ( input % testFactor == 0 )
            output.insert(testFactor);
	if ( include_self )
        output.insert(input);
	return output;
}
const vector<long long> EulerUtils::NumberTheory::Factorise::primeFactorsAll( long long input ) {
    vector<long long> output;
    long long remain = input;
    // If input is equal to or greater than one, add one to the factor list and carry on,
    // otherwise, return an empty vector
    if ( input > 0 ) {
        output.push_back(1);
        if ( input == 1 )
            return output;
    } else
        return output;
    for ( long long testFactor = 2 ; testFactor <= input/2 ; testFactor++ ) {
        if ( Prime::isPrime( testFactor ) )
            while ( remain % testFactor == 0 ) {
                output.push_back(testFactor);
                remain /= testFactor;
            }
    }
    if ( Prime::isPrime(input) ) output.push_back(input);
    return output;
}
// TODO update this function (was allFactors()) to
// vector<long>& 0EulerUtils::primeFactors( long long input, bool unique )
vector<long long> EulerUtils::NumberTheory::Factorise::primeFactorsSet( long long input ) {
	vector<long long> output;
	for ( long long testFactor = 2 ; testFactor <= input/2 ; testFactor++ ) {
        cout << "input = " << input << " and testFactor = " << testFactor << endl;
		if ( input % testFactor == 0 && Prime::isPrime( testFactor ) ) {
			output.push_back(testFactor);
			cout << testFactor << " added!" << endl;
		}
	}
	if ( Prime::isPrime(input) ) output.push_back(input);
	return output;
}
bool EulerUtils::NumberTheory::General::even(long long n) {
    if ( n < 0) n = n * -1;
    return (n&1==1);
}
long long EulerUtils::NumberTheory::General::product( vector<long long> input ) {
    long long result = 1;
    for ( auto i = input.begin() ; i < input.end() ; i++ ) {
        result *= *i;
    }
    return result;
}
void EulerUtils::NumberTheory::General::rotate_int( unsigned int *x ) {
    string x_str = to_string(*x);
    unsigned short len = x_str.size();
    *x = (unsigned short)stoi( x_str.substr(1)+x_str.substr(0,1) );
}
unsigned int EulerUtils::NumberTheory::General::rotate_int( unsigned int x ) {
    string x_str = to_string(x);
    unsigned short len = x_str.size();
    return (unsigned short)stoi( x_str.substr(1)+x_str.substr(0,1) );
}
string EulerUtils::NumberTheory::General::rotate_str( string x ) {
    return x.substr(1)+x.substr(0,1);
}
vector<unsigned long long> EulerUtils::NumberTheory::Prime::gatherPrimesUpTo( unsigned long long n ) {
    vector<unsigned long long> primes;
    for ( unsigned long long i = 1 ; i <= n ; i++ ) {
        if ( isPrime(i) ) primes.push_back(i);
    }
    return primes;
}
bool EulerUtils::NumberTheory::Prime::isPrime( unsigned long long input ) {
    if ( input < 2 ) return false;
    unsigned long long lim = floor(sqrt(input));
	for( unsigned long long test = 2 ; test <= lim ; ++test )
		if( input % test == 0 )
			return false;
	return true;
}
unsigned long long EulerUtils::NumberTheory::Prime::nextPrime( unsigned long long input ){
	unsigned long long current = input;
	while (true)
		if ( Prime::isPrime(++current) )
			return current;
	return 0;
}
unsigned long long EulerUtils::NumberTheory::Prime::nthPrime( unsigned long long n ) {
	unsigned long long current, tally;
	for ( current = 2, tally = 0 ; tally < n ; current++ )
		if ( Prime::isPrime( current ) )
			tally ++;
	return --current;

}
unsigned long long EulerUtils::NumberTheory::Prime::primesFactorial( unsigned long long n ) {
    if ( n == 2 ) return n;
    else {
        if ( Prime::isPrime( n ) )
            return primesFactorial( n-1 ) * n;
        else
            return primesFactorial( n-1 );
    }
}
const unsigned long long EulerUtils::NumberTheory::Special::nthTriangularNumber( const unsigned long long n ) {
    unsigned long long sum = 0;
    for ( unsigned long long current = 1 ; current <= n ; ++current )
        sum += current;
    return sum;
}
int EulerUtils::NumberTheory::Special::addDigits( string input ) {
    int total = 0;
    for ( int c = 0 ; c < input.size() ; ++c )
        total += std::stoi( input.substr(c,1) );
    return total;
}
const unsigned long long EulerUtils::NumberTheory::Special::Fibonacci::nthFibonacciNumber_recursion( const unsigned long long n ) {
    if ( n==0 ) return 0;
    if ( n==1 || n==2 ) return 1;
    return nthFibonacciNumber_recursion(n-1) + nthFibonacciNumber_recursion(n-2);
}
const unsigned long long EulerUtils::NumberTheory::Special::Fibonacci::nthFibonacciNumber_iteration( const unsigned long long n ) {
    if ( n==0 ) return 0;
    unsigned long long lhs=1, rhs=1;
    for ( unsigned long long current = 1 ; current <= n ; ++current ) {
        unsigned temp = lhs+rhs;
        lhs = rhs;
        rhs = temp;
    }
    return lhs;
}
const unsigned long long EulerUtils::NumberTheory::Special::Fibonacci::fibonacciLessThanN( unsigned long long n ) {
    // TODO fill
    return 0;
}
const bool EulerUtils::NumberTheory::Special::Pandigital::isPandigital( string x ) {
    set<unsigned short> digits;
    // Init digits...
    for ( unsigned short digit = 1 ; digit < 10 ; ++digit ) {
        digits.insert(digit);
//        cout << "digit : " << digit << endl;
    }
    for ( auto i = 0 ; i < x.size() ; ++i ) {
        string ch = x.substr(i,1);
        digits.erase((unsigned short)stoi(ch));
    }

    return digits.size() == 0;
}
const bool EulerUtils::NumberTheory::Special::Pandigital::isPandigital( unsigned int x ) {
    return isPandigital( to_string(x) );
}
const short EulerUtils::NumberTheory::Special::Perfect::isDeficientPerfectOrAbundant( const unsigned long long n ) {
    unsigned long long sum = 1;
    for ( unsigned long long factor = 2 ; factor <= n/2 ; ++factor )
        if ( n%factor == 0 )
            sum += factor;
    if ( sum < n ) return -1;
    if ( sum > n ) return 1;
    return 0;
}
const bool EulerUtils::NumberTheory::Special::Perfect::isPerfect( const unsigned long long n ) {
    unsigned long long sum = 1;
    for ( unsigned long long factor = 2 ; factor <= n/2 ; ++factor )
        if ( n%factor == 0 )
            sum += factor;
    return sum==n;
}



/************************************************************************
*************************************************************************
*******************************  SEARCH  ********************************
*************************************************************************
************************************************************************/

// TODO kill one of the following two...
int EulerUtils::Search::countAppearance( vector<long long> haystack, long long needle ) {
    int count = 0;
    for ( auto i = haystack.begin() ; i < haystack.end() ; i++ ) {
        if ( *i == needle ) ++count;
    }
    return count;
}
const int EulerUtils::Search::countItem( const vector<long long> haystack, const long long needle ) {
    int tally = 0;
    for ( auto i : haystack ) {
        if ( i == needle ) {
            ++tally;
        }
    }
    return tally;
}
bool EulerUtils::Search::inVector( vector<long long>& haystack, long long needle ) {
	for ( vector<long long>::iterator iter = haystack.begin() ; iter != haystack.end() ; iter++ )
		if ( *iter == needle ) return true;
	return false;
}
map<long long, int> EulerUtils::Search::contentTally( vector<long long> collection ) {
    map<long long, int> output;
    for ( auto i = collection.begin() ; i < collection.end() ; i++ ) {
        long long item = *i;
        cout << "test - item: " << item << endl;
    }
    return output;
}





/*************************************************************************
**************************************************************************
*******************************  STRINGS  ********************************
**************************************************************************
*************************************************************************/

string EulerUtils::Strings::float_to_string( const long double val, const int n ){
    std::ostringstream out;
    out << std::setprecision(n) << val;
    return out.str();
}
const std::vector<std::string> EulerUtils::Strings::split( const std::string &s, char delim ) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        if (item.length() > 0) {
            elems.push_back(item);
        }
    }
    return elems;
}
const std::vector<int> EulerUtils::Strings::splitToInt( const std::string &s, char delim ) {
    std::vector<int> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        if (item.length() > 0) {
            elems.push_back(std::atoi(item.c_str()));
        }
    }
    return elems;
}
EulerUtils::Strings::splitstring::splitstring( char *s ) : string( s ) { };
vector<string>& EulerUtils::Strings::splitstring::split(char delim, int rep) {
    if (!this->flds.empty()) this->flds.clear();  // empty vector if necessary
    string work = data();
    string buf = "";
    int i = 0;
    while (i < work.length()) {
        if (work[i] != delim)
            buf += work[i];
        else if (rep == 1) {
            flds.push_back(buf);
            buf = "";
        } else if (buf.length() > 0) {
            flds.push_back(buf);
            buf = "";
        }
        i++;
    }
    if (!buf.empty())
        flds.push_back(buf);
    return flds;
}
// TODO create a function that takes a collection of strings and combines them
int EulerUtils::Strings::strToInt ( string input ) {
	int output;
	try {
		output = boost::lexical_cast<int>( input );
		return output;
	} catch( boost::bad_lexical_cast const& ) {
	    cout << "Error: " << input << " was not converted to an int!" << endl;
	    return -1;
	}
}
// TODO create a function that takes a collection of strings and combines them
template <class N>
string EulerUtils::Strings::numToString( N num ){
    string out = boost::lexical_cast<string>(num);
    return out;
}





/*************************************************************************
**************************************************************************
********************************  TO DO  *********************************
**************************************************************************
*************************************************************************/

//vector<long long> EulerUtils::integerDivisors( long long input ) {
//	vector<long long> output;
//	for ( long long testFactor = 1 ; testFactor <= input/2 ; testFactor++ ) {
//		if ( input % testFactor == 0 ) {
//			output.push_back(testFactor);
//		}
//	}
//	return output;
//}


// get grids
/*  FIRST ATTEMPTS
const string ** EulerUtils::CustomData::GridArr::getStrGrid() {
	return const_cast<string**>(this->str_grid);
}
const int ** EulerUtils::GridArr::getIntGrid() {
	// TODO check this after next build
	const int ** out = const_cast<int**>(this->int_grid);
	return out;
//return const_cast<int**>(this->int_grid);
}
*/


//template<typename I>
//long long EulerUtils::nthTriangularNumber( I term ) {
//    long long sum = 0;
//    for ( long long current = 1 ; current <= term ; ++current ) {
//        sum += current;
//    }
//    return sum;
//}


//template <typename T>
//std::string EulerUtils::float_to_string( const T val, const int n ){
//    std::ostringstream out;
//    out << std::setprecision(n) << val;
//    return out.str();
//}


/*
EulerUtils::StrInt::StrInt ( string input ) {
    string temp_val= "",
           temp_block = "";
    int strlen = input.size(),
        blocks = 0,
        remain = 0;
    try {
//        // If the input exceeds a block...
//        if ( strlen > this->BLOCK_MAX ) {
        blocks = (int)(strlen/this->BLOCK_MAX);
        remain = (int)(strlen%this->BLOCK_MAX);
        for ( int block_start = 0 ; input.substr(block_start).size() > 0 ; i += this->BLOCK_MAX ) {
            temp_block = input.substr( block_start, this->BLOCK_MAX );
            long long temp_int = std::stoll( input.substr(block_start) );
            if ( EulerUtils::ngtv( std::stoll( input.substr(block_start) ) ) && block_start != 0 ) {
                cout << "Exception in EulerUtils::StrInt::StrInt( string input ) - Negative non-starting block!" << endl;
                delete this;
            }
            temp_val += temp_block;
        }
//        }
    } catch ( const std::invalid_argument& ex ) {
        cout << "Exception in EulerUtils::StrInt::StrInt( string input ) - " << ex.what() << endl;
    }
}
EulerUtils::StrInt::virtual ~StrInt () {
}

EulerUtils::StrInt::string _get () {
}
EulerUtils::StrInt::bool _set ( string input ) {
}
EulerUtils::StrInt::bool _set ( StrInt input ) {
}

EulerUtils::StrInt::int col ( int ten_pow ) {
}
EulerUtils::StrInt::int len () {
    return ( this->pstv()   ?
        this->val.size()    :
        this->val.size()-1  ;
}
EulerUtils::StrInt::int max () {
    return this->BLOCK_MAX;
}
EulerUtils::StrInt::bool pstv() {
    return ( (char)(this->val[0]) != '-' ) ;
}

/* Arithmetic Operators */
/*
EulerUtils::StrInt::StrInt operator+ ( StrInt lhs, StrInt rhs ) {

}
EulerUtils::StrInt::StrInt operator- ( StrInt lhs, StrInt rhs ) {
}
EulerUtils::StrInt::StrInt operator* ( StrInt lhs, StrInt rhs ) {
}
EulerUtils::StrInt::StrInt operator/ ( StrInt lhs, StrInt rhs ) {
}
EulerUtils::StrInt::StrInt operator% ( StrInt lhs, StrInt rhs ) {
}
*/
/* Comparison Operators */
/*
EulerUtils::StrInt::bool operator==( StrInt lhs, StrInt rhs );
EulerUtils::StrInt::bool operator>=( StrInt lhs, StrInt rhs );
EulerUtils::StrInt::bool operator<=( StrInt lhs, StrInt rhs );
EulerUtils::StrInt::bool operator>( StrInt lhs, StrInt rhs );
EulerUtils::StrInt::bool operator<( StrInt lhs, StrInt rhs );

EulerUtils::StrInt::StrInt factorial();

protected:

private:
    string val;
    int len;
}
*/
