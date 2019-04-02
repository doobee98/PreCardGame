#pragma once

namespace ViewConfig {
	namespace GAME {
		enum { WIDTH = 20, HEIGHT = 20, X = 0, Y = 0 };
	}
	namespace AI_ALL {
		enum { WIDTH = 18, HEIGHT = 2, X = GAME::X + 1, Y = GAME::Y + 1 };
	}
	namespace AI {
		enum { WIDTH = 5, HEIGHT = 2 };
	}
	namespace DECK {
		enum { WIDTH = 4, HEIGHT = 1, X = GAME::X + 3, Y = GAME::Y + 5 };
	}
	namespace FIELD {
		enum { WIDTH = 18, HEIGHT = 1, X = GAME::X + 9, Y = GAME::Y + 5 };
	}
	namespace TURNDIR {
		enum { WIDTH = 4, HEIGHT = 1, X = GAME::X + 9, Y = GAME::Y + 4};
	}
	namespace USER {
		enum { WIDTH = 5, HEIGHT = 2, X = GAME::X + 8, Y = GAME::Y + 8 };
	}
	namespace LOG {
		enum { WIDTH = 20, HEIGHT = 1, X = GAME::X + 4, Y = GAME::Y + 12 };
	}
	namespace USER_HAND {
		enum { WIDTH = 20, HEIGHT = 5, X = GAME::X + 1, Y = GAME::Y + 16, ROW_NUM = 5, COL_NUM = 3 };
	}
}