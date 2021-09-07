#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

class Utils {
  public:
	/**
	 * @brief Split a string where a ch is found and store the resulting
	 * substring in a vector. Returns the size of the vector
	 *
	 * @param txt
	 * @param strs
	 * @param ch
	 * @return unsigned int
	 */
	static unsigned int
	split(const std::string& txt, std::vector<std::string>& strs, char ch) {
		int pos = txt.find(ch);
		int initialPos { };
		strs.clear( );
		while (pos != std::string::npos) {
			strs.push_back(txt.substr(initialPos, pos - initialPos + 1));
			initialPos = pos + 1;

			pos = txt.find(ch, initialPos);
		}

		strs.push_back(
			txt.substr(initialPos,
					   std::min<int>(pos, txt.size( ) - (initialPos + 1))));

		return strs.size( );
	}

  private:
};

#endif