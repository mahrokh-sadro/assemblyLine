// Name:Mahrokh Sadrolodabaee
// Seneca Student ID:159436195
// Seneca email:msadrolodabaee@myseneca.ca
// Date of completion:July 21,2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "CustomerOrder.h"
#include "Utilities.h"
#include "Station.h"


using namespace std;
namespace sdds {

	size_t CustomerOrder::m_widthField{};


	CustomerOrder::CustomerOrder(const std::string& order)
	{
		Utilities utility;
		size_t next_pos{};
		bool more = true;
		string token;

		try {
			m_name = utility.extractToken(order, next_pos, more);
            m_product = utility.extractToken(order, next_pos, more);

			vector<string> items;
			while (more) {
				string item = utility.extractToken(order, next_pos, more);
				items.push_back(item);
			}
		
			m_cntItem = items.size();
			m_lstItem = new Item * [m_cntItem];

			for (size_t i = 0; i < m_cntItem; i++) {
				m_lstItem[i] = new Item(items[i]);
			}

			m_widthField = max(utility.getFieldWidth(), m_widthField);

		}
		catch (string& err) {
			cout << err;
		}
	}
	CustomerOrder::CustomerOrder(const CustomerOrder& n)
	{
		throw string("ERROR: Cannot make copies.");
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& n) noexcept
	{
		*this = move(n);
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& n) noexcept
	{
		if (this != &n) {
			myDeallocation();
			m_name = n.m_name;
			n.m_name = "";
			m_product = n.m_product;
			n.m_product = "";
			m_cntItem = n.m_cntItem;
			n.m_cntItem = 0;
			m_lstItem = n.m_lstItem;
			n.m_lstItem = nullptr;
			m_widthField = n.m_widthField;

		}
		return *this;
	}
	
	bool CustomerOrder::isFilled() const
	{
		bool filled = true;
		for (size_t i = 0; i < m_cntItem && filled; i++) {
			filled = m_lstItem[i]->m_isFilled;
		}
		return filled;
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool filled = true;
		for (size_t i = 0; i < m_cntItem && filled; i++) {
			if (m_lstItem[i]->m_itemName == itemName) {
				filled = m_lstItem[i]->m_isFilled;
			}
		}
		return filled;
	}
	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName()) {
				if (station.getQuantity()) {
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os << "    Filled " << m_name << ", " << m_product << " ["
						<< m_lstItem[i]->m_itemName << "]" << endl;
				}
				else {
					os << "    Unable to fill " << m_name << ", " << m_product
						<< " [" << m_lstItem[i]->m_itemName << "]" << endl;
				}
			}
		}
	}
	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << right << "[" << setw(6) << setfill('0') << m_lstItem[i]->m_serialNumber << "] "
				<< left << setfill(' ') << setw(m_widthField) << m_lstItem[i]->m_itemName
				<< left << (m_lstItem[i]->m_isFilled ? " - FILLED" : " - TO BE FILLED") << endl;
		}
	}

	CustomerOrder::~CustomerOrder()  {myDeallocation();}

	void CustomerOrder::myDeallocation()
	{
		for (size_t i = 0; i < m_cntItem; i++) delete m_lstItem[i];
		delete[] m_lstItem;
	}

}
