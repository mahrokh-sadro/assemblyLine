// Name:Mahrokh Sadrolodabaee
// Seneca Student ID:159436195
// Seneca email:msadrolodabaee@myseneca.ca
// Date of completion:July 21,2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <algorithm>
#include <iostream>
#include <fstream>
#include "LineManager.h"
#include "Utilities.h"

using namespace std;
namespace sdds {
	
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)//not done yet
	{
		Utilities u;
		std::ifstream f(file);
		if (!f)   throw std::string("error, cannot open file");	
		else
		{
			std::string str;    
			std::string current;   
			std::string next;  
			bool more;
			size_t pos = 0;
			Workstation* currentSt{};     
			Workstation* nextSt{};       
			Workstation* firstSt{};    
			while (std::getline(f, str))
			{
				current = u.extractToken(str, pos, more);   
				currentSt = *std::find_if(stations.begin(), stations.end(), [&](Workstation* stations) {
					return stations->getItemName() == current;
					});
				activeLine.push_back(currentSt);  
				if (more) 
				{
					next = u.extractToken(str, pos, more);
					nextSt = *std::find_if(stations.begin(), stations.end(), [&](Workstation* stations) {
						return stations->getItemName() == next;
						});
					currentSt->setNextStation(nextSt);
				}
			}
			for_each(stations.begin(), stations.end(), [&](Workstation* tmp) {
				firstSt = *find_if(stations.begin(), stations.end(), [&](Workstation* station) {
					return station->getNextStation() == firstSt;
					});
				});
			m_firstStation = firstSt; 
		}
	
		m_cntCustomerOrder = pending.size();  
	}

	
		void LineManager::linkStations()
		{

			const Workstation* station = m_firstStation;
			size_t i = 0;
			do
			{
				activeLine[i++] = const_cast<Workstation*>(station);
				station = station->getNextStation();
			} while (station );
		}
	
		bool LineManager::run(std::ostream & os)
		{
			bool ret = false;
			static size_t count{1};    
			os << "Line Manager Iteration: " << count << std::endl;

			if (!pending.empty())
			{
				*m_firstStation += std::move(pending.front());
				pending.pop_front();
			}


			for (size_t i = 0; i < activeLine.size(); i++)
			{
				activeLine[i]->fill(os);
			}

			for (size_t i = 0; i < activeLine.size(); i++)
			{
				activeLine[i]->attemptToMoveOrder();
			}

			if (completed.size() + incomplete.size() == m_cntCustomerOrder)
			{
				ret = true;
			}
			++count;
			return ret;
		}
	
		void LineManager::display(std::ostream & os) const
		{
			
			for (size_t i = 0; i < activeLine.size(); i++)
			{
				activeLine[i]->display(os);
			}
			
		}
	

}



