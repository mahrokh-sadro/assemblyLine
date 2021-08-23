// Name:Mahrokh Sadrolodabaee
// Seneca Student ID:159436195
// Seneca email:msadrolodabaee@myseneca.ca
// Date of completion:July 21,2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.



#include <string>
#include <vector>
#include <iostream>
#include "Workstation.h"
using namespace std;
namespace sdds {

	std::deque<CustomerOrder> pending{};//to b filled
	std::deque<CustomerOrder> completed{};
	std::deque<CustomerOrder> incomplete{};



	Workstation::Workstation(const std::string& n):Station(n){}

	
	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty()) 	m_orders.front().fillItem(*this, os);

	}
	
	bool Workstation::attemptToMoveOrder()
	{
		bool ret = false;
		if (!m_orders.empty()) {
			if (m_orders.front().isItemFilled(getItemName())) {
				if (!m_pNextStation) {
					if (m_orders.front().isFilled()) completed.push_back(std::move(m_orders.front())); 
					else incomplete.push_back(std::move(m_orders.front()));
				}
				else {
					*m_pNextStation += move(m_orders.front());
				}
				m_orders.pop_front();
				ret = true;
			}
			else if (!getQuantity()) {    
				if (!m_pNextStation) {
					incomplete.push_back(move(m_orders.front()));
				}
				else {
					*m_pNextStation += move(m_orders.front());
				}
				m_orders.pop_front();
				ret = true;
			}

		}
		return ret;
	}

	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = & *station;

	}

	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os) const
	{
		if (m_pNextStation) os << getItemName() << " --> " << getNextStation()->getItemName();
		else                os << getItemName() << " --> " << "End of Line";
		os << endl;
		
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(move(newOrder));
		return *this;
	}

}


