#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <string>
#include "Headerfiles/header.hpp"
#include <math.h>

using namespace std;
using namespace sf;

class Restaurant;
void displayfoodinfo(Restaurant *, Text **);

class FoodItem
{
protected:
	string name;
	float price;
	int servingsize;
	string vegetarian;
	string halal;
	string dir;

public:
	string getName() const { return name; }
	float getPrice() const { return price; }
	int getServingsize() const { return servingsize; }
	string getVegetarian() const { return vegetarian; }
	string getHalal() const { return halal; }
	string getdir() { return dir; }
	void setName(string newName) { name = newName; }
	void setPrice(float newPrice) { price = newPrice; }
	void setServingsize(int newServingsize) { servingsize = newServingsize; }
	void setVegetarian(string newVegetarian) { vegetarian = newVegetarian; }
	void setHalal(string newHalal) { halal = newHalal; }
	FoodItem() {}
	FoodItem(const std::string &name, float price, int servingsize, string vegetarian, string halal, string dir)
		: name(name), price(price), servingsize(servingsize), vegetarian(vegetarian), halal(halal), dir(dir)
	{

	}
	virtual ~FoodItem() {}
};
class Order
{
private:
	string coupon;
	string couponstatus;
	double delivery;
	float discount;
	float subtotal1 = 0;
	float subtotal2 = 0;
	float subtotal3 = 0;
	int numitem1 = 0;
	int numitem2 = 0;
	int numitem3 = 0;
	string item1;
	string item2;
	string item3;
	float price1;
	float price2;
	float price3;
public:
	Order() {}
	Order(float discount, double delivery) : delivery(delivery), discount(discount)
	{

	}
	double calculatetotal()
	{
		if (subtotal1 + subtotal2 + subtotal3 == 0)return 0;
		if (coupon == "BSCSB")return (subtotal1 + subtotal2 + subtotal3 + delivery)*(1.0 - discount);
		else return (subtotal1 + subtotal2 + subtotal3 + delivery);
	}
	void setcoupon(string coupon) {
		this->coupon = coupon;
		if (coupon == "BSCSB")
		{
			couponstatus = "VALID COUPON CODE!";
		}
		else
		{
			couponstatus = "INVALID COUPON CODE!";
		}
	}
	void setSubtotal1(float value) { subtotal1 = value; }
	void setSubtotal2(float value) { subtotal2 = value; }
	void setSubtotal3(float value) { subtotal3 = value; }
	float getSubtotal1() const { return subtotal1; }
	float getSubtotal2() const { return subtotal2; }
	float getSubtotal3() const { return subtotal3; }
	void setitem1(string item1) { this->item1 = item1; }
	void setitem2(string item2) { this->item2 = item2; }
	void setitem3(string item3) { this->item3 = item3; }
	string getitem1() { return item1; }
	string getitem2() { return item2; }
	string getitem3() { return item3; }
	void setprice1(float price1) { this->price1 = price1; }
	void setprice2(float price2) { this->price2 = price2; }
	void setprice3(float price3) { this->price3 = price3; }
	float getprice1() { return price1; }
	float getprice2() { return price2; }
	float getprice3() { return price3; }
	int getNumItem1() const { return numitem1; }
	void setNumItem1(int value) { numitem1 = value; }
	int getNumItem2() const { return numitem2; }
	void setNumItem2(int value) { numitem2 = value; }
	int getNumItem3() const { return numitem3; }
	void setNumItem3(int value) { numitem3 = value; }
	const string &getCouponStatus() const { return couponstatus; }
};
class Restaurant
{
protected:
	string name;
	string location;
	string days;
	string timings;
	float discount;
	double delivery;
	int stars;
	double restauranttotal = 0;
	FoodItem *menu[3];
	Texture texture;
public:
	Order order;
	string getName() const { return name; }
	string getLocation() const { return location; }
	string getDays() const { return days; }
	string getTimings() const { return timings; }
	float getDiscount() const { return discount; }
	double getDelivery() const { return delivery; }
	int getStars() const { return stars; }
	FoodItem **getmenu() { return menu; }
	Texture getTexture() { return texture; }
	void setName(string newName) { name = newName; }
	void setLocation(string newLocation) { location = newLocation; }
	void setDays(string newDays) { days = newDays; }
	void setTimings(string newTimings) { timings = newTimings; }
	void setDiscount(float newDiscount) { discount = newDiscount; }
	void setDelivery(double newDelivery) { delivery = newDelivery; }
	void setStars(int newStars) { stars = newStars; }
	Restaurant(string name, string location, string days, string timings, float discount, double delivery, int stars, string dir)
		: name(name), location(location), days(days), timings(timings), discount(discount), delivery(delivery), stars(stars)
	{
		texture.loadFromFile(dir);
		order = Order(discount, delivery);
	}
	void updatecart(Text& cart1, Text& cart2, Text& cart3, Text& carttotal) {
		order.setSubtotal1(order.getNumItem1()*menu[0]->getPrice());
		if (order.getSubtotal1() != 0)cart1.setString(menu[0]->getName() + " x(" + to_string(order.getNumItem1()) + ")\n" + "SUBTOTAL: " + to_string(order.getSubtotal1()).substr(0, 7) + "/- Rs");
		else cart1.setString(menu[0]->getName() + " x(" + to_string(order.getNumItem1()) + ")\n" + "SUBTOTAL: " + "0.00/- Rs");
		order.setSubtotal2(order.getNumItem2()*menu[1]->getPrice());
		if (order.getSubtotal2() != 0)cart2.setString(menu[1]->getName() + " x(" + to_string(order.getNumItem2()) + ")\n" + "SUBTOTAL: " + to_string(order.getSubtotal2()).substr(0, 7) + "/- Rs");
		else cart2.setString(menu[1]->getName() + " x(" + to_string(order.getNumItem2()) + ")\n" + "SUBTOTAL: " + "0.00/- Rs");
		order.setSubtotal3(order.getNumItem3()*menu[2]->getPrice());
		if (order.getSubtotal3() != 0)cart3.setString(menu[2]->getName() + " x(" + to_string(order.getNumItem3()) + ")\n" + "SUBTOTAL: " + to_string(order.getSubtotal3()).substr(0, 7) + "/- Rs");
		else cart3.setString(menu[2]->getName() + " x(" + to_string(order.getNumItem3()) + ")\n" + "SUBTOTAL: " + "0.00/- Rs");
		if (order.calculatetotal() != 0)carttotal.setString("TOTAL: " + to_string(order.calculatetotal()).substr(0, 7));
		else carttotal.setString("TOTAL: 0.00/- Rs");
	}
	virtual void additem(FoodItem *item) = 0;
};
class Burger : public FoodItem
{
private:
	string meat;
	string bun;
	string sauce;
public:
	string getMeat() const { return meat; }
	string getBun() const { return bun; }
	string getSauce() const { return sauce; }
	void setMeat(string newMeat) { meat = newMeat; }
	void setBun(string newBun) { bun = newBun; }
	void setSauce(string newSauce) { sauce = newSauce; }
	Burger(string name, float price, int servingsize, string vegetarian, string halal, string meat, string bun, string sauce, string dir) : FoodItem(name, price, servingsize, vegetarian, halal, dir), meat(meat), bun(bun), sauce(sauce) {}
};
class Pizza : public FoodItem
{
private:
	string toppings;
	string flavour;
	string crust;
public:
	string getToppings() const { return toppings; }
	string getFlavour() const { return flavour; }
	string getCrust() const { return crust; }
	void setToppings(string newToppings) { toppings = newToppings; }
	void setFlavour(string newFlavour) { flavour = newFlavour; }
	void setCrust(string newCrust) { crust = newCrust; }
	Pizza(string name, float price, int servingsize, string vegetarian, string halal, string toppings, string flavour, string crust, string dir) : FoodItem(name, price, servingsize, vegetarian, halal, dir), toppings(toppings), flavour(flavour), crust(crust) {}
};
class Fries : public FoodItem
{
private:
	string salt;
	string condiments;
	string size;
public:
	string getSalt() const { return salt; }
	string getCondiments() const { return condiments; }
	string getSize() const { return size; }
	void setSalt(string newSalt) { salt = newSalt; }
	void setCondiments(string newCondiments) { condiments = newCondiments; }
	void setSize(string newSize) { size = newSize; }
	Fries(string name, float price, int servingsize, string vegetarian, string halal, string salt, string condiments, string size, string dir) : FoodItem(name, price, servingsize, vegetarian, halal, dir), salt(salt), condiments(condiments), size(size) {}
};
class Fastfood : public Restaurant
{
public:
	Fastfood(string name, string location, string days, string timings, float discount, double delivery, int stars, string dir)
		: Restaurant(name, location, days, timings, discount, delivery, stars, dir)
	{
	}
	void additem(FoodItem *item)
	{ /// using dynamic casting to determine which type of FoodItem
		Burger *ptr1 = dynamic_cast<Burger *>(item);
		if (ptr1 != nullptr)
		{
			order.setitem1(ptr1->getName());
			order.setprice1(ptr1->getPrice());
			menu[0] = ptr1;
			return;
		}
		Pizza *ptr2 = dynamic_cast<Pizza *>(item);
		if (ptr2 != nullptr)
		{
			order.setitem2(ptr2->getName());
			order.setprice2(ptr2->getPrice());
			menu[1] = ptr2;
			return;
		}
		Fries *ptr3 = dynamic_cast<Fries *>(item);
		if (ptr3 != nullptr)
		{
			order.setitem3(ptr3->getName());
			order.setprice3(ptr3->getPrice());
			menu[2] = ptr3;
			return;
		}
	}
};
class Karahi : public FoodItem
{
private:
	string meat;
	string masala;
	string spicy;
public:
	string getMeat() const { return meat; }
	string getMasala() const { return masala; }
	string getSpicy() const { return spicy; }
	void setMeat(string newMeat) { meat = newMeat; }
	void setMasala(string newType) { masala = newType; }
	void setSpicy(string newSpicy) { spicy = newSpicy; }
	Karahi(string name, float price, int servingsize, string vegetarian, string halal, string meat, string masala, string spicy, string dir) : FoodItem(name, price, servingsize, vegetarian, halal, dir), meat(meat), masala(masala), spicy(spicy) {}
};
class BBQ : public FoodItem
{
private:
	string meat;
	string masala;
	string charred;
public:
	string getMeat() const { return meat; }
	string getMasala() const { return masala; }
	string getCharred() const { return charred; }
	void setMeat(string newMeat) { meat = newMeat; }
	void setMasala(string newMasala) { masala = newMasala; }
	void setCharred(string newCharred) { charred = newCharred; }
	BBQ(string name, float price, int servingsize, string vegetarian, string halal, string meat, string masala, string charred, string dir) : FoodItem(name, price, servingsize, vegetarian, halal, dir), meat(meat), masala(masala), charred(charred) {}
};
class Biryani : public FoodItem
{
private:
	string meat;
	string rice;
	string origin;
public:
	string getMeat() const { return meat; }
	string getRice() const { return rice; }
	string getOrigin() const { return origin; }
	void setMeat(string newMeat) { meat = newMeat; }
	void setRice(string newRice) { rice = newRice; }
	void setOrigin(string newOrigin) { origin = newOrigin; }
	Biryani(string name, float price, int servingsize, string vegetarian, string halal, string meat, string rice, string origin, string dir) : FoodItem(name, price, servingsize, vegetarian, halal, dir), meat(meat), rice(rice), origin(origin) {}
};
class Desi : public Restaurant
{
public:
	Desi(string name, string location, string days, string timings, float discount, double delivery, int stars, string dir)
		: Restaurant(name, location, days, timings, discount, delivery, stars, dir) {}
	void additem(FoodItem *item)
	{ /// using dynamic casting to determine which type of FoodItem
		Karahi *ptr1 = dynamic_cast<Karahi *>(item);
		if (ptr1 != nullptr)
		{
			menu[0] = ptr1;
			return;
		}
		BBQ *ptr2 = dynamic_cast<BBQ *>(item);
		if (ptr2 != nullptr)
		{
			menu[1] = ptr2;
			return;
		}
		Biryani *ptr3 = dynamic_cast<Biryani *>(item);
		if (ptr3 != nullptr)
		{
			menu[2] = ptr3;
			return;
		}
	}
};
class Icecream : virtual public FoodItem
{
private:
	string cone;
	string scoops;
protected:
	string flavour;
public:
	string getFlavour() const { return flavour; }
	void setFlavour(const string &newFlavour) { flavour = newFlavour; }
	string getCone() const { return cone; }
	void setCone(const string &newCone) { cone = newCone; }
	string getScoops() const { return scoops; }
	void setScoops(const string &newScoops) { scoops = newScoops; }
	Icecream(string name, float price, int servingsize, string vegetarian, string halal, string cone, string flavour, string scoops, string dir) : FoodItem(name, price, servingsize, vegetarian, halal, dir), cone(cone), flavour(flavour), scoops(scoops) {}
	Icecream() {}
};
class Shake : virtual public FoodItem
{
private:
	string milk;
	string temperature;
protected:
	string flavour;
public:
	string getMilk() const { return milk; }
	void setMilk(const string newMilk) { milk = newMilk; }
	string getTemperature() const { return temperature; }
	void setTemperature(const string newTemperature) { temperature = newTemperature; }
	string getFlavour() const { return flavour; }
	void setFlavour(const string newFlavour) { flavour = newFlavour; }
	Shake() {}
	Shake(string name, float price, int servingsize, string vegetarian, string halal, string milk, string flavour, string temperature, string dir) : FoodItem(name, price, servingsize, vegetarian, halal, dir), milk(milk), flavour(flavour), temperature(temperature) {}
};
class Icecreamshake : public Icecream, public Shake
{
private:
	string toppings;
	string creaminess;
public:
	string getFlavour() { return Shake::flavour; }
	void setFlavour(string newFlavour) { Shake::flavour = newFlavour; }
	Icecreamshake(string name, float price, int servingsize, string vegetarian, string halal, string toppings, string flv, string creaminess, string dir) : FoodItem(name, price, servingsize, vegetarian, halal, dir), toppings(toppings), creaminess(creaminess) { setFlavour(flv); }
	string getToppings() { return toppings; }
	void setToppings(string newToppings) { toppings = newToppings; }
	string getCreaminess() { return creaminess; }
	void setCreaminess(string newCreaminess) { creaminess = newCreaminess; }
};
class Dessert : public Restaurant
{
public:
	Dessert(string name, string location, string days, string timings, float discount, double delivery, int stars, string dir)
		: Restaurant(name, location, days, timings, discount, delivery, stars, dir)
	{

	}
	void additem(FoodItem *item)
	{
		Icecreamshake *ptr3 = dynamic_cast<Icecreamshake *>(item);
		if (ptr3 != nullptr)
		{
			menu[2] = ptr3;
			return;
		}
		Icecream *ptr1 = dynamic_cast<Icecream *>(item);
		if (ptr1 != nullptr)
		{
			menu[0] = ptr1;
			return;
		}
		Shake *ptr2 = dynamic_cast<Shake *>(item);
		if (ptr2 != nullptr)
		{
			menu[1] = ptr2;
			return;
		}
	}
};
class State
{
public:
	string current = "home";
	Restaurant *restaurant = nullptr;
};
class App
{
public:
	double grand_total = 0;
	Fastfood restaurant1;
	Desi restaurant2;
	Dessert restaurant3;
	void setrestaurant(Fastfood &restaurant)
	{
		restaurant1 = restaurant;
	}
	void setrestaurant(Desi &restaurant)
	{
		restaurant2 = restaurant;
	}
	void setrestaurant(Dessert &restaurant)
	{
		restaurant3 = restaurant;
	}
	void updategrandtotal(double amount)
	{
		grand_total += amount;
	}
	double getgrandtotal()
	{
		return grand_total;
	}
};
int main()
{
	srand(time(NULL));
	State state;
	Karahi koilakarahi("Koila Karahi", 1100, 4, "Non-Vegetarian", "Halal", "Meat: Chicken, ", "Special Karahi Masala, ", "Spicy", "Resources/karahi.png");
	BBQ reshmi("Reshmi Kabab", 900, 2, "Non-Vegetarian", "Halal", "Meat: Beef, ", "Masala: Afghani, ", "Charred", "Resources/bbq.png");
	Biryani sindhibiryani("Sindhi Biryani", 600, 1, "Non-Vegetarian", "Halal", "Meat: Chicken, ", "Rice: Basmati Rice, ", "Origin: Sindhi", "Resources/biryani.jpg");
	Desi desipoint("Desi Point", "Hayatabad", "Mon-Sat", "12pm to 12am", 0.1, 60, 4, "Resources/desipointposter.png");
	desipoint.additem(&koilakarahi);
	desipoint.additem(&reshmi);
	desipoint.additem(&sindhibiryani);
	Burger zinger("Zinger Burger", 700, 1, "Non-Vegetarian", "Meat: Chicken, ", "Bun: Brioche bun, ", "Sauce: Thousand Islands Sauce, ", "Resources/burger.png");
	Pizza fajita("Fajita Pizza", 1200, 5, "Non-Vegetarian", "Toppings: Mushrooms, ", "Flavour: Fajita, ", "Stuffed Crust", "Resources/pizza.png");
	Fries fries("French Fries", 100, 1, "Vegetarian", "Light salt, ", "Ketchup, ", "Size: Small", "Resources/fries.jpg");
	Fastfood texaschicken("Texas Chicken", "HBK, Ring Road", "Mon - Sun", "11am to 1am", 0.1, 100, 4, "Resources/texaschickenposter.png");
	texaschicken.additem(&zinger);
	texaschicken.additem(&fajita);
	texaschicken.additem(&fries);
	Icecream gelato("Gelato", 350, 1, "Vegetarian", "Halal", "Waffle Cone, ", "Chocolate Flavour, ", "3 Scoops, ", "Resources/icecream.png");
	Shake shake("Milk Shake", 400, 1, "Vegetarian", "Halal", "Almond Milk", "Strawberry", "70 degree Celcius", "Resources/shake.jpg");
	Icecreamshake icecreamshake("Ice-cream Shake", 600, 2, "Vegetarian", "Halal", "Cherries, ", "Chocolate, ", "Extra creamy", "Resources/icecreamshake.jpg");
	cout << icecreamshake.getdir();
	Dessert shakeshack("Shake Shack", "University Town", "Mon-Sat", "11am to 11pm", 0.1, 120, 5, "Resources/shakeshackposter.png");
	shakeshack.additem(&gelato);
	shakeshack.additem(&shake);
	shakeshack.additem(&icecreamshake);
	RenderWindow window(VideoMode(1200, 650), "Foodpanda", Style::Close | Style::Titlebar);
	window.setFramerateLimit(60);
	RectangleShape hit(Vector2f(1, 1));
	Image logoimg;
	logoimg.loadFromFile("Resources/foodpandalogo.png");
	window.setIcon(logoimg.getSize().x, logoimg.getSize().y, logoimg.getPixelsPtr());
	RectangleShape bg(Vector2f(window.getSize()));
	bg.setFillColor(Color::White);
	Font font;
	font.loadFromFile("Resources/Poppins-Regular.ttf");
	Text texttemplate;
	texttemplate.setFont(font);
	texttemplate.setCharacterSize(35);
	texttemplate.setStyle(Text::Regular);
	texttemplate.setFillColor(Color(184, 32, 101));
	texttemplate.setLetterSpacing(1);
	Texture back;
	back.loadFromFile("Resources/back.png");
	Text welcome = texttemplate;
	welcome.setString(" Welcome to Foodpanda, discount on coupon code BSCSB!");
	Text welcome2 = welcome;
	welcome2.setPosition(Vector2f(-10000, welcome2.getPosition().y));
	RectangleShape banner(Vector2f(bg.getSize().x, welcome.getGlobalBounds().height + 15));
	banner.setFillColor(Color::White);
	banner.setOutlineColor(Color(184, 32, 101));
	banner.setOutlineThickness(4);
	Texture titletex;
	titletex.loadFromFile("Resources/foodpandatitle.png");
	RectangleShape title(Vector2f(banner.getSize().x / 4.9, banner.getSize().y));
	title.setOutlineThickness(4);
	title.setOutlineColor(Color(184, 32, 101));
	title.setPosition(banner.getPosition());
	title.setTexture(&titletex);
	RectangleShape card1(Vector2f(bg.getSize().x / 4, bg.getSize().y + -200));
	card1.setPosition(Vector2f(bg.getSize().x / 16, banner.getSize().y + 20));
	card1.setFillColor(Color(184, 32, 101));
	RectangleShape poster1(Vector2f(card1.getSize().x, card1.getSize().y / 3 + 30));
	poster1.setPosition(card1.getPosition());
	RectangleShape card2 = card1;
	card2.setPosition(Vector2f(card1.getPosition().x + card1.getSize().x + bg.getSize().x / 16, card1.getPosition().y));
	card2.setFillColor(Color(184, 32, 101));
	RectangleShape poster2 = poster1;
	poster2.setPosition(card2.getPosition());
	RectangleShape card3 = card1;
	card3.setPosition(Vector2f(card2.getPosition().x + card2.getSize().x + bg.getSize().x / 16, card1.getPosition().y));
	card3.setFillColor(Color(184, 32, 101));
	RectangleShape poster3(Vector2f(card1.getSize().x, card1.getSize().y / 3 + 30));
	poster3.setPosition(card3.getPosition());
	Text name1 = texttemplate; name1.setCharacterSize(23);
	name1.setFillColor(Color::White);
	name1.setPosition(poster1.getPosition().x + 10, poster1.getPosition().y + poster1.getSize().y + 3);
	name1.setStyle(Text::Bold);
	Text rating1 = texttemplate;
	rating1.setPosition(name1.getPosition().x, name1.getPosition().y + 50);
	rating1.setCharacterSize(20);
	rating1.setFillColor(Color::White);
	Text location1 = rating1;
	location1.setPosition(rating1.getPosition().x, rating1.getPosition().y + 30);
	Text schedule1 = location1;
	schedule1.setPosition(location1.getPosition().x, location1.getPosition().y + 30);
	Text delivery1 = schedule1;
	delivery1.setPosition(schedule1.getPosition().x, schedule1.getPosition().y + 30);
	Text discount1 = delivery1;
	discount1.setPosition(delivery1.getPosition().x, delivery1.getPosition().y + 30);
	Text name2 = name1;
	name2.setPosition(poster2.getPosition().x + 10, poster2.getPosition().y + poster2.getSize().y + 3);
	Text rating2 = rating1;
	rating2.setPosition(name2.getPosition().x, name2.getPosition().y + 50);
	Text location2 = rating2;
	location2.setPosition(rating2.getPosition().x, rating2.getPosition().y + 30);
	Text schedule2 = location2;
	schedule2.setPosition(location2.getPosition().x, location2.getPosition().y + 30);
	Text delivery2 = schedule2;
	delivery2.setPosition(schedule2.getPosition().x, schedule2.getPosition().y + 30);
	Text discount2 = delivery2;
	discount2.setPosition(delivery2.getPosition().x, delivery2.getPosition().y + 30);
	Text name3 = name1;
	name3.setPosition(poster3.getPosition().x + 10, poster3.getPosition().y + poster3.getSize().y + 3);
	Text rating3 = rating1;
	rating3.setPosition(name3.getPosition().x, name3.getPosition().y + 50);
	Text location3 = rating3;
	location3.setPosition(rating3.getPosition().x, rating3.getPosition().y + 30);
	Text schedule3 = location3;
	schedule3.setPosition(location3.getPosition().x, location3.getPosition().y + 30);
	Text delivery3 = schedule3;
	delivery3.setPosition(schedule3.getPosition().x, schedule3.getPosition().y + 30);
	Text discount3 = delivery3;
	discount3.setPosition(delivery3.getPosition().x, delivery3.getPosition().y + 30);
	RectangleShape total(Vector2f(card1.getSize().x, banner.getSize().y));
	total.setPosition(card2.getPosition().x, 530);
	total.setFillColor(Color(184, 32, 101));
	Text totaltext = texttemplate;
	totaltext.setFillColor(Color::White);
	totaltext.setPosition(Vector2f(total.getPosition().x + 10, total.getPosition().y + 5));
	totaltext.setString("Total Sales: ");
	totaltext.setCharacterSize(20);
	// item1
	RectangleShape item1(Vector2f(bg.getSize().x / 4, bg.getSize().y - 260));
	item1.setPosition(card1.getPosition());
	item1.setFillColor(Color(184, 32, 101));
	RectangleShape i1(Vector2f(item1.getSize().x / 1.4, card1.getSize().y / 3 + 30));
	i1.setPosition(item1.getPosition().x + (item1.getSize().x - i1.getSize().x) / 2, item1.getPosition().y + 1);
	Text foodname1 = name1;
	foodname1.setPosition(i1.getPosition().x, i1.getPosition().y + i1.getSize().y + 5);
	Text price1 = rating1; price1.setCharacterSize(15);
	price1.setPosition(foodname1.getPosition().x, foodname1.getPosition().y + 30);
	Text serving1 = price1;
	serving1.setPosition(price1.getPosition().x, price1.getPosition().y + 20);
	Text veg1 = serving1;
	veg1.setPosition(serving1.getPosition().x, serving1.getPosition().y + 20);
	Text halal1 = veg1;
	halal1.setPosition(veg1.getPosition().x, veg1.getPosition().y + 20);
	// item2
	RectangleShape item2(Vector2f(bg.getSize().x / 4, bg.getSize().y - 260));
	item2.setPosition(card2.getPosition());
	item2.setFillColor(Color(184, 32, 101));
	RectangleShape i2(Vector2f(item1.getSize().x / 1.4, card1.getSize().y / 3 + 30));
	i2.setPosition(item2.getPosition().x + (item1.getSize().x - i1.getSize().x) / 2, item1.getPosition().y + 1);
	Text foodname2 = foodname1;
	foodname2.setPosition(i2.getPosition().x, i2.getPosition().y + i2.getSize().y + 5);
	Text price2 = price1;
	price2.setPosition(foodname2.getPosition().x, foodname2.getPosition().y + 50);
	Text serving2 = price2;
	serving2.setPosition(price2.getPosition().x, price2.getPosition().y + 30);
	Text veg2 = serving2;
	veg2.setPosition(serving2.getPosition().x, serving2.getPosition().y + 30);
	Text halal2 = veg2;
	halal2.setPosition(veg2.getPosition().x, veg2.getPosition().y + 30);
	// item3
	RectangleShape item3(Vector2f(bg.getSize().x / 4, bg.getSize().y - 260));
	item3.setPosition(card3.getPosition());
	item3.setFillColor(Color(184, 32, 101));
	RectangleShape i3(Vector2f(item1.getSize().x / 1.4, card1.getSize().y / 3 + 30));
	i3.setPosition(item3.getPosition().x + (item1.getSize().x - i1.getSize().x) / 2, item1.getPosition().y + 1);
	Text foodname3 = foodname1;
	foodname3.setPosition(i3.getPosition().x, i3.getPosition().y + i3.getSize().y + 5);
	Text price3 = price1;
	price3.setPosition(foodname3.getPosition().x, foodname3.getPosition().y + 50);
	Text serving3 = price3;
	serving3.setPosition(price3.getPosition().x, price3.getPosition().y + 30);
	Text veg3 = serving3;
	veg3.setPosition(serving3.getPosition().x, serving3.getPosition().y + 30);
	Text halal3 = veg3;
	halal3.setPosition(veg3.getPosition().x, veg3.getPosition().y + 30);
	Text *foodarr[15] = {
		&foodname1,
		&foodname2,
		&foodname3,
		&price1,
		&price2,
		&price3,
		&serving1,
		&serving2,
		&serving3,
		&veg1,
		&veg2,
		&veg3,
		&halal1,
		&halal2,
		&halal3 };
	RectangleShape cart(Vector2f(banner.getSize().x, banner.getSize().y + 100));
	cart.setOutlineThickness(4);
	cart.setOutlineColor(Color(184, 32, 101));
	cart.setPosition(0, bg.getSize().y - cart.getSize().y);
	Text carttext = totaltext;
	carttext.setFillColor(Color(184, 32, 101));
	carttext.setString("YOUR CART: (click on the cart item to remove it)");
	carttext.setPosition(1, cart.getPosition().y - 30);
	Text cart1 = texttemplate; cart1.setCharacterSize(19);
	cart1.setPosition(item1.getPosition().x, item1.getPosition().y + item1.getSize().y + 40);
	Text cart2 = cart1;
	cart2.setPosition(item2.getPosition().x, item1.getPosition().y + item1.getSize().y + 40);
	Text cart3 = cart1;
	cart3.setPosition(item3.getPosition().x, item1.getPosition().y + item1.getSize().y + 40);
	RectangleShape checkout = total; checkout.setScale(0.5, 0.5);
	checkout.setPosition(checkout.getPosition().x + 550, checkout.getPosition().y + 70);
	Text checkouttext = totaltext;
	checkouttext.setString("Checkout");
	checkouttext.setCharacterSize(20);
	checkouttext.setPosition(checkout.getPosition().x + 20, checkout.getPosition().y + 1);
	Text coupon = checkouttext;
	coupon.setString("Coupon: ");
	coupon.setPosition(coupon.getPosition().x - 1000, coupon.getPosition().y - 15);
	coupon.setStyle(Text::Bold);
	coupon.setFillColor(welcome.getFillColor());
	Text couponinput = coupon; couponinput.setString("");
	couponinput.setPosition(coupon.getPosition().x + 100, coupon.getPosition().y);
	Text carttotal = coupon;
	carttotal.setPosition(checkouttext.getPosition().x - 300, checkouttext.getPosition().y);
	carttotal.setStyle(Text::Bold);
	carttotal.setString("Total:");
	std::string temp;
	Texture tex1 = texaschicken.getTexture();
	Texture tex2 = shakeshack.getTexture();
	Texture tex3 = desipoint.getTexture();
	poster1.setTexture(&tex1);
	poster2.setTexture(&tex2);
	poster3.setTexture(&tex3);
	name1.setString(texaschicken.getName());
	name2.setString(shakeshack.getName());
	name3.setString(desipoint.getName());
	location1.setString("> " + texaschicken.getLocation());
	location2.setString("> " + shakeshack.getLocation());
	location3.setString("> " + desipoint.getLocation());
	schedule1.setString("> " + texaschicken.getDays() + " " + texaschicken.getTimings());
	schedule2.setString("> " + shakeshack.getDays() + " " + shakeshack.getTimings());
	schedule3.setString("> " + desipoint.getDays() + " " + desipoint.getTimings());
	rating1.setString("> " + to_string(texaschicken.getStars()) + " star rating");
	rating2.setString("> " + to_string(shakeshack.getStars()) + " star rating");
	rating3.setString("> " + to_string(desipoint.getStars()) + " star rating");
	delivery1.setString("> " + to_string(floor(texaschicken.getDelivery())).substr(0, 5) + "/- Rs Delivery Charges");
	delivery2.setString("> " + to_string(floor(shakeshack.getDelivery())).substr(0, 5) + "/- Rs Delivery Charges");
	delivery3.setString("> " + to_string(floor(desipoint.getDelivery())).substr(0, 5) + "/- Rs Delivery Charges");
	discount1.setString("> " + to_string(floor(texaschicken.getDiscount() * 100)).substr(0, 5) + "\% off on code BSCSB");
	discount2.setString("> " + to_string(floor(shakeshack.getDiscount() * 100)).substr(0, 5) + "\% off on code BSCSB");
	discount3.setString("> " + to_string(floor(desipoint.getDiscount() * 100)).substr(0, 5) + "\% off on code BSCSB");
	Texture t1;
	Texture t2;
	Texture t3;
	Sprite sprite1;
	Sprite sprite2;
	Sprite sprite3;
	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
			if (e.type == Event::MouseMoved)
				hit.setPosition(Vector2f(Mouse::getPosition(window)));
			if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left && state.current == "menu") {
				if (hit.getGlobalBounds().intersects(item1.getGlobalBounds())) {
					state.restaurant->order.setNumItem1(state.restaurant->order.getNumItem1() + 1);
				}
				else if (hit.getGlobalBounds().intersects(item2.getGlobalBounds())) {
					state.restaurant->order.setNumItem2(state.restaurant->order.getNumItem2() + 1);
				}
				else if (hit.getGlobalBounds().intersects(item3.getGlobalBounds())) {
					state.restaurant->order.setNumItem3(state.restaurant->order.getNumItem3() + 1);
				}
				else if (hit.getGlobalBounds().intersects(cart1.getGlobalBounds())) {
					if (state.restaurant->order.getNumItem1() > 0) state.restaurant->order.setNumItem1(state.restaurant->order.getNumItem1() - 1);
				}
				else if (hit.getGlobalBounds().intersects(cart2.getGlobalBounds())) {
					if (state.restaurant->order.getNumItem2() > 0)state.restaurant->order.setNumItem2(state.restaurant->order.getNumItem2() - 1);
				}
				else if (hit.getGlobalBounds().intersects(cart3.getGlobalBounds())) {
					if (state.restaurant->order.getNumItem3() > 0)state.restaurant->order.setNumItem3(state.restaurant->order.getNumItem3() - 1);
				}
				state.restaurant->updatecart(cart1, cart2, cart3, carttotal);
			}
			if (e.type == Event::TextEntered && state.current == "menu")
			{
				if ((e.text.unicode < 91 && e.text.unicode > 64 && temp.size() < 5) || (e.text.unicode < 123 && e.text.unicode > 96 && temp.size() < 6))
				{
					temp += static_cast<char>(e.text.unicode);
					state.restaurant->order.setcoupon(temp);
					couponinput.setString(temp + "\n" + state.restaurant->order.getCouponStatus());
					state.restaurant->updatecart(cart1, cart2, cart3, carttotal);
				}
				else if (e.text.unicode == '\b' && !couponinput.getString().isEmpty())
				{
					temp.pop_back();
					state.restaurant->order.setcoupon(temp);
					couponinput.setString(temp + "\n" + state.restaurant->order.getCouponStatus());
					state.restaurant->updatecart(cart1, cart2, cart3, carttotal);
				}
			}
		}
		window.clear();
		window.draw(bg);
		window.draw(banner);
		window.draw(welcome);
		window.draw(welcome2);
		window.draw(title);
		welcome.move(Vector2f(2, 0));
		welcome2.move(Vector2f(2, 0));
		if ((welcome.getGlobalBounds().left + welcome.getGlobalBounds().width) == bg.getSize().x)
			welcome2.setPosition(Vector2f(0 - welcome2.getGlobalBounds().width, welcome2.getPosition().y));
		if ((welcome2.getGlobalBounds().left + welcome2.getGlobalBounds().width) == bg.getSize().x)
			welcome.setPosition(Vector2f(0 - welcome.getGlobalBounds().width, welcome.getPosition().y));
		if (state.current == "home")
		{
			if ((welcome.getGlobalBounds().left + welcome.getGlobalBounds().width) == bg.getSize().x)
				welcome2.setPosition(Vector2f(0 - welcome2.getGlobalBounds().width, welcome2.getPosition().y));
			if ((welcome2.getGlobalBounds().left + welcome2.getGlobalBounds().width) == bg.getSize().x)
				welcome.setPosition(Vector2f(0 - welcome.getGlobalBounds().width, welcome.getPosition().y));
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (hit.getGlobalBounds().intersects(card1.getGlobalBounds()))
				{
					state.current = "menu";
					state.restaurant = &texaschicken;
					state.restaurant->updatecart(cart1, cart2, cart3, carttotal);
					displayfoodinfo(state.restaurant, foodarr);
					t1.loadFromFile(zinger.getdir());
					t2.loadFromFile(fajita.getdir());
					t3.loadFromFile(fries.getdir());
				}
				else if (hit.getGlobalBounds().intersects(card2.getGlobalBounds())) {
					state.current = "menu";
					state.restaurant = &shakeshack;
					state.restaurant->updatecart(cart1, cart2, cart3, carttotal);
					displayfoodinfo(state.restaurant, foodarr);
					t1.loadFromFile(gelato.getdir());
					t2.loadFromFile(shake.getdir());
					t3.loadFromFile(icecreamshake.getdir());
				}
				else if (hit.getGlobalBounds().intersects(card3.getGlobalBounds())) {
					state.current = "menu";
					state.restaurant = &desipoint;
					state.restaurant->updatecart(cart1, cart2, cart3, carttotal);
					displayfoodinfo(state.restaurant, foodarr);
					t1.loadFromFile(koilakarahi.getdir());
					t2.loadFromFile(reshmi.getdir());
					t3.loadFromFile(sindhibiryani.getdir());
				}
				else if (hit.getGlobalBounds().intersects(total.getGlobalBounds())) {
					totaltext.setString("meh");
				}
				sprite1.setTexture(t1);
				sprite1.setTextureRect(IntRect(0, 0, i1.getSize().x, i1.getSize().y));
				sprite1.setPosition(i1.getPosition());
				sprite2.setTexture(t2);
				sprite2.setTextureRect(IntRect(0, 0, i2.getSize().x, i2.getSize().y));
				sprite2.setPosition(i2.getPosition());
				sprite3.setTexture(t3);
				sprite3.setTextureRect(IntRect(0, 0, i3.getSize().x, i3.getSize().y));
				sprite3.setPosition(i3.getPosition());
			}
			window.draw(card1);
			window.draw(card2);
			window.draw(card3);
			window.draw(poster1);
			window.draw(poster2);
			window.draw(poster3);
			window.draw(total);
			window.draw(totaltext);
			window.draw(name1);
			window.draw(name2);
			window.draw(name3);
			window.draw(rating1);
			window.draw(rating2);
			window.draw(rating3);
			window.draw(location1);
			window.draw(location2);
			window.draw(location3);
			window.draw(schedule1);
			window.draw(schedule2);
			window.draw(schedule3);
			window.draw(delivery1);
			window.draw(delivery2);
			window.draw(delivery3);
			window.draw(discount1);
			window.draw(discount2);
			window.draw(discount3);
		}
		else if (state.current == "menu")
		{
			title.setTexture(&back);
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (hit.getGlobalBounds().intersects(title.getGlobalBounds()))
				{
					state.restaurant->order.setNumItem1(0);
					state.restaurant->order.setNumItem2(0);
					state.restaurant->order.setNumItem3(0);
					title.setTexture(&titletex);
					state.current = "home";
				}
			}
			window.draw(item1);
			window.draw(item2);
			window.draw(item3);
			window.draw(cart);
			window.draw(carttext);
			window.draw(sprite1);
			window.draw(sprite2);
			window.draw(sprite3);
			window.draw(cart1);
			window.draw(cart2);
			window.draw(cart3);
			window.draw(checkout);
			window.draw(checkouttext);
			window.draw(coupon);
			window.draw(couponinput);
			window.draw(carttotal);
			window.draw(foodname1);
			window.draw(foodname2);
			window.draw(foodname3);
			window.draw(price1);
			window.draw(price2);
			window.draw(price3);
			window.draw(serving1);
			window.draw(serving2);
			window.draw(serving3);
			window.draw(veg1);
			window.draw(veg2);
			window.draw(veg3);
			window.draw(halal1);
			window.draw(halal2);
			window.draw(halal3);
		}
		window.display();
	};
}
void displayfoodinfo(Restaurant *r, Text **foodarr)
{
	foodarr[0]->setString("> " + r->getmenu()[0]->getName());
	foodarr[1]->setString("> " + r->getmenu()[1]->getName());
	foodarr[2]->setString("> " + r->getmenu()[2]->getName());
	foodarr[3]->setString("> " + to_string((r->getmenu()[0])->getPrice()).substr(0, 6) + "/- Rs");
	foodarr[4]->setString("> " + to_string((r->getmenu()[1])->getPrice()).substr(0, 6) + "/- Rs");
	foodarr[5]->setString("> " + to_string((r->getmenu()[2])->getPrice()).substr(0, 6) + "/- Rs");
	foodarr[6]->setString("> " + to_string((r->getmenu()[0])->getServingsize()) + " persons");
	foodarr[7]->setString("> " + to_string((r->getmenu()[1])->getServingsize()) + " persons");
	foodarr[8]->setString("> " + to_string((r->getmenu()[2])->getServingsize()) + " persons");
	foodarr[9]->setString("> " + r->getmenu()[0]->getVegetarian());
	foodarr[10]->setString("> " + r->getmenu()[1]->getVegetarian());
	foodarr[11]->setString("> " + r->getmenu()[2]->getVegetarian());
	foodarr[12]->setString("> " + r->getmenu()[0]->getHalal());
	foodarr[13]->setString("> " + r->getmenu()[1]->getHalal());
	foodarr[14]->setString("> " + r->getmenu()[2]->getHalal());
}