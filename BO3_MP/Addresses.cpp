#include "Addresses.hpp"

Addresses::Addresses() {

}

Addresses::~Addresses() {
	memset(this, 0, sizeof(Addresses));
}

Addresses * addresses;

