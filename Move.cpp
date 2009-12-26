#include "Move.h"
#include "Board.h"
#include <iostream>

std::ostream& operator<<(std::ostream& o, const Move& m) {
	return (o << square2string(m.From()) << square2string(m.To()) );
}
