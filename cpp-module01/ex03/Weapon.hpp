#ifndef WEAPON_HPP
#define WEAPON_HPP
#include <string>

class Weapon {
public:
	explicit Weapon(const std::string& s);
	~Weapon();
	const std::string& getType() const;
	void setType(const std::string& new_type);

private:
	std::string type_;
};

#endif
