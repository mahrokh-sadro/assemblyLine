// Name:Mahrokh Sadrolodabaee
// Seneca Student ID:159436195
// Seneca email:msadrolodabaee@myseneca.ca
// Date of completion:July 21,2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

#include <string>
#include <vector>
#include "Workstation.h"

namespace sdds {
	
	class LineManager{
	
		std::vector<Workstation*> activeLine;
		size_t m_cntCustomerOrder{};
		Workstation* m_firstStation{};

	public:

		LineManager(const std::string& , const std::vector<Workstation*>& stations);
		void linkStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;

	};

}

#endif