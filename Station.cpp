// Name:Mahrokh Sadrolodabaee
// Seneca Student ID:159436195
// Seneca email:msadrolodabaee@myseneca.ca
// Date of completion:July 21,2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#include <iostream>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"
using namespace std;
namespace sdds {

	size_t Station::m_widthField{};
	size_t Station::id_generator{1};

	Station::Station(const std::string& str)
	{
		m_id = id_generator;
		Utilities util;
		size_t next_pos = 0;
		bool more = true;

		try
		{
			m_name = util.extractToken(str, next_pos, more);
			m_serialNumber = stoi(util.extractToken(str, next_pos, more));
			m_itemsInStock = stoi(util.extractToken(str, next_pos, more));
			m_widthField = max(util.getFieldWidth(), m_widthField);
			m_description = util.extractToken(str, next_pos, more);
		}
		catch (string& msg)
		{
			cout << msg;
		}
		id_generator++;
	}

	const std::string& Station::getItemName() const
	{
		return m_name;
	}

	size_t Station::getNextSerialNumber()
	{
		
		return m_serialNumber++;
	}

	size_t Station::getQuantity() const
	{
		return m_itemsInStock;
	}

	void Station::updateQuantity()
	{
		if(m_itemsInStock>0)  --m_itemsInStock;

	}
	
	void Station::display(std::ostream& os, bool full) const
	{
				
			os <<right << "[" <<setfill('0') << setw(3) <<  m_id;
			os<< "]"<< left<<" Item: ";
			os << setw(m_widthField) << setfill(' ') << left << getItemName();
			os<<right	<< " [" << setw(6)<<setfill('0') <<  m_serialNumber <<"]";
				
			if (full) {
			
				os <<   " Quantity: " <<left<< setfill(' ') << setw(2)<< getQuantity()
				   <<right  << setw(26)<< "Description: "<<m_description;
				
		    }

		os << endl;
	}

	

}