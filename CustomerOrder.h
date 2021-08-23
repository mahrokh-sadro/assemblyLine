// Name:Mahrokh Sadrolodabaee
// Seneca Student ID:159436195
// Seneca email:msadrolodabaee@myseneca.ca
// Date of completion:July 21,2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H

#include <string>
#include "Station.h"
namespace sdds {

	class CustomerOrder {

		struct Item
		{
			std::string m_itemName;
			size_t m_serialNumber{};
			bool m_isFilled{};

			Item(const std::string& src) : m_itemName(src) {};
		};

		std::string m_name;
		std::string m_product;
		size_t m_cntItem{};
		Item** m_lstItem{};
		static size_t m_widthField;
		void myDeallocation();
	public:
		CustomerOrder() {};
		CustomerOrder(const std::string&);
		CustomerOrder(const CustomerOrder&);
		CustomerOrder& operator=(const CustomerOrder&)=delete;
		CustomerOrder(CustomerOrder&&) noexcept;
		CustomerOrder& operator=(CustomerOrder&&) noexcept;
		bool isFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
		virtual ~CustomerOrder();

	};

}

#endif

