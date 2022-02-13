#include<iostream>
#include<string>
#include<vector>
#include <fstream>
#include <sstream>
using namespace std;
class Ticket {
private:
	char* roomName;
	int seatNr;
	char* movieName;
	int hour;
	int price;
	bool isAvailable;

public:
	Ticket() {
	}

	Ticket(char* roomName, int seatNr, char* filmName, int hour, int price) {
		this->isAvailable = true;
		this->roomName = new char[strlen(roomName) + 1];
		strcpy_s(this->roomName, strlen(roomName) + 1, roomName);
		this->seatNr = seatNr;
		this->movieName = new char[strlen(filmName) + 1];
		strcpy_s(this->movieName, strlen(filmName) + 1, filmName);
		this->hour = hour;
		this->price = price;
	}

	Ticket(const Ticket& t)
	{
		if (t.roomName != nullptr)
		{
			this->roomName = new char[strlen(t.roomName) + 1];
			strcpy_s(this->roomName, strlen(t.roomName) + 1, t.roomName);
		}
		this->seatNr = t.seatNr;
		if (t.movieName != nullptr)
		{
			this->movieName = new char[strlen(t.movieName) + 1];
			strcpy_s(this->movieName, strlen(t.movieName) + 1, t.movieName);
		}
		this->hour = t.hour;
		this->price = t.price;
	}

	~Ticket()
	{
		if (roomName != nullptr)
		{
			delete[] roomName;
		}

		if (movieName != nullptr)
		{
			delete[] movieName;
		}
	}

	Ticket& operator=(const Ticket& t)
	{
		if (roomName != nullptr)
		{
			delete[] roomName;
		}

		if (movieName != nullptr)
		{
			delete[] movieName;
		}

		if (t.roomName != nullptr)
		{
			this->roomName = new char[strlen(t.roomName) + 1];
			strcpy_s(this->roomName, strlen(t.roomName) + 1, t.roomName);
		}
		else
		{
			this->roomName = nullptr;
		}
		this->seatNr = t.seatNr;
		if (t.movieName != nullptr)
		{
			this->movieName = new char[strlen(t.movieName) + 1];
			strcpy_s(this->movieName, strlen(t.movieName) + 1, t.movieName);
		}
		else
		{
			this->movieName = nullptr;
		}
		this->hour = t.hour;
		this->price = t.price;

		return *this;
	}

	char* getroomName()
	{
		return roomName;
	}

	int getseatNr()
	{
		return seatNr;
	}

	char* getfilmName()
	{
		return movieName;
	}

	int gethour()
	{
		return hour;
	}

	bool getIsAvailable() {
		return this->isAvailable;
	}

	void setIsAvailable(bool isAvailable) {
		this->isAvailable = isAvailable;
	}


	int getprice()
	{
		return price;
	}


	Ticket operator+(int valoare)//operator + 
	{
		Ticket copie = *this;
		copie.seatNr += valoare;
		return copie;
	}


	Ticket operator++()//operatorul de preincrementare
	{
		this->seatNr++;
		return *this;
	}


	Ticket operator++(int i)//operatorul de postincrementare
	{
		Ticket copie = *this;
		this->seatNr++;
		return copie;
	}


	explicit operator int()//operator de cast la int explicit
	{
		return seatNr;
	}

	bool operator!()//operatorul de negatie
	{
		return seatNr > 0;
	}

	bool operator<(Ticket t)//operator conditional
	{
		return this->seatNr < t.seatNr;
	}

	friend ostream& operator<<(ostream&, Ticket&);
	friend istream& operator>>(istream&, Ticket&);
};

class Schedule {
private:
	int* hours;
	int hoursSize;
	int roomId;
public:
	Schedule() {
	}
	Schedule(const int hours[], int hoursSize, int roomId) {
		this->roomId = roomId;
		this->hoursSize = hoursSize;
		if (hours != nullptr) {
			this->hours = new int[hoursSize];

			for (int i = 0; i < hoursSize; i++) {
				this->hours[i] = hours[i];
			}
		}
		else {
			this->hours = nullptr;
		}
	}

	~Schedule() {
		if (hours != nullptr) {
			delete[] hours;
			hours = nullptr;
		}
	}

	Schedule(const Schedule& s) {
		this->roomId = s.roomId;
		if (this->hours != nullptr) {
			delete[] this->hours;
			hours = nullptr;
			this->hoursSize = 0;
		}
		if (s.hours != nullptr && s.hoursSize != 0) {
			this->hoursSize = s.hoursSize;
			this->hours = new int[s.hoursSize];
			for (int i = 0; i < s.hoursSize; i++) {
				this->hours[i] = s.hours[i];
			}
		}
	}

	Schedule& operator=(const Schedule& s) {
		this->roomId = s.roomId;
		if (this->hours != nullptr) {
			delete[] this->hours;
			this->hours = nullptr;
			this->hoursSize = 0;
		}
		if (s.hours != nullptr && s.hoursSize != 0) {
			this->hoursSize = s.hoursSize;
			this->hours = new int[s.hoursSize];
			for (int i = 0; i < s.hoursSize; i++) {
				this->hours[i] = s.hours[i];
			}
		}
	}


	int* getHours() {
		return this->hours;
	}

	void setHour(int* hours, int hoursSize) {
		this->hoursSize = hoursSize;
		if (hours != nullptr && hoursSize != 0) {
			this->hours = hours; // SHALLOW copy
		}
		else {
			if (this->hours != nullptr)
			{
				delete[] hours;
				this->hours = nullptr;
				this->hoursSize = 0;
			}
		}
	}
	void setRoomId(int roomId) {
		this->roomId = roomId;
	}

	int getRoomId() {
		return roomId;
	}

	int getHourSize() {
		return hoursSize;
	}


	friend ostream& operator<<(ostream&, Schedule&);
	friend istream& operator>>(istream&, Schedule&);
};

class Movie
{
private:
	static int counter;
	int movieId;
	char* movieName;
	string genre;
	int length;
	Schedule* schedule;
	int price;


public:
	Movie()
	{
		movieName = new char[11]{ "Necunoscut" };
		length = 0;
		this->schedule = nullptr;
		price = 0;
		movieId = counter++;
	}

	Movie(const char* movieName, int price)
	{
		this->price = price;
		this->movieName = new char[strlen(movieName) + 1];
		strcpy_s(this->movieName, strlen(movieName) + 1, movieName);
		this->schedule = nullptr;
		//roomId = 0;
		movieId = counter++;


	}

	Movie(const Movie& f)
	{
		movieId = f.movieId;
		//roomId = f.roomId; 
		this->price = f.price;
		if (f.movieName != nullptr)
		{
			this->movieName = new char[strlen(f.movieName) + 1];
			strcpy_s(this->movieName, strlen(f.movieName) + 1, f.movieName);
		}
		else
		{
			this->movieName = nullptr;
		}

		this->length = f.length;

		if (f.schedule != nullptr)
		{
			this->schedule = new Schedule(*f.schedule); // DE verificat daca merge dupa ce implementam operatorii din Schedule
		}
		else {
			this->schedule = nullptr;
		}

	}

	Movie& operator=(const Movie& f)
	{
		//roomId = f.roomId;
		movieId = f.movieId;
		this->price = f.price;
		if (movieName != nullptr)
		{
			delete[] movieName;
			movieName = nullptr;
		}

		if (schedule != nullptr)
		{
			delete schedule;
			schedule = nullptr;
		}

		if (f.movieName != nullptr)
		{
			this->movieName = new char[strlen(f.movieName) + 1];
			strcpy_s(this->movieName, strlen(f.movieName) + 1, f.movieName);
		}

		if (f.schedule != nullptr)
		{
			this->schedule = new Schedule(*f.schedule);
		}
		this->length = f.length;
		return *this;
	}

	~Movie()
	{
		if (movieName != nullptr)
		{
			delete[] movieName;
			movieName = nullptr;
		}

		if (schedule != nullptr)
		{
			delete schedule;
			schedule = nullptr;
		}
	}

	char* getMovieName()
	{
		return movieName;
	}


	string getGenre()
	{
		return genre;
	}

	int getLength()
	{
		return length;
	}

	void setPrice(int price) {
		this->price = price;
	}

	int getPrice() {
		return this->price;
	}

	/*int getRoomId() {
		return roomId;
	}

	void setRoomId(int roomId) {
		this->roomId = roomId;
	}*/

	int getMovieId() {
		return movieId;
	}


	Schedule* getSchedule()
	{
		return schedule;
	}

	void setSchedule(Schedule* schedule)
	{
		if (schedule != nullptr)
		{
			delete this->schedule;
			this->schedule = nullptr;
			this->schedule = new Schedule(*schedule);
		}
	}

	Movie operator+(int valoare)//operator + 
	{
		Movie copie = *this;
		copie.length += valoare;
		return copie;
	}


	Movie operator++()//operatorul de preincrementare
	{
		this->length++;
		return *this;
	}


	Movie operator++(int i)//operatorul de postincrementare
	{
		Movie copie = *this;
		this->length++;
		return copie;
	}


	explicit operator int()//operator de cast la int explicit
	{
		return length;
	}

	bool operator<(Movie f)//operator conditional
	{
		return this->length < f.length;
	}

	friend ostream& operator<<(ostream&, Movie&);
	friend istream& operator>>(istream&, Movie&);
};

class Room
{
private:
	static int counter;
	int roomId; //this can be static and incremented into constructors
	Movie* movie;
	char* roomName;
	int nrOfSeats;
	std::vector<std::vector<Ticket>> tickets;
public:

	std::vector<Ticket>& getSeatsByHourId(int id) {
		return tickets.at(id);
	}
	Room() {
		roomId = counter++;
		roomName = nullptr;
		movie = nullptr;
		nrOfSeats = 0;

	}

	Room(const char* roomName, int nrOfSeats) {
		this->roomId = counter++;
		movie = nullptr;
		this->roomName = new char[strlen(roomName) + 1];
		strcpy_s(this->roomName, strlen(roomName) + 1, roomName);
		if (nrOfSeats != 0)
		{
			this->nrOfSeats = nrOfSeats;
		}
	}

	Room(const Room& r)
	{
		movie = r.movie;
		this->roomId = r.roomId;
		if (r.roomName != nullptr)
		{
			this->roomName = new char[strlen(r.roomName) + 1];
			strcpy_s(this->roomName, strlen(r.roomName) + 1, r.roomName);
		}
		this->nrOfSeats = r.nrOfSeats;
	}

	~Room()
	{
		if (roomName != nullptr)
		{
			delete[] roomName;
		}
	}

	Room& operator=(const Room& r)
	{
		this->movie = r.movie;
		this->roomId = counter++;
		this->nrOfSeats = r.nrOfSeats;
		if (roomName != nullptr)
		{
			delete[] roomName;
		}
		if (r.roomName != nullptr)
		{
			this->roomName = new char[strlen(r.roomName) + 1];
			strcpy_s(this->roomName, strlen(r.roomName) + 1, r.roomName);
		}
		else
		{
			this->roomName = nullptr;
		}
		return *this;
	}

	int getRoomId()
	{
		return roomId;
	}

	char* getRoomName()
	{
		return roomName;
	}

	int getNrOfSeats()
	{
		return nrOfSeats;
	}

	void setMovie(Movie* movie) {

		this->movie = movie;
	}

	Movie* getMovie() {
		return movie;
	}

	Room operator+(int valoare)//operator +
	{
		Room copie = *this;
		copie.nrOfSeats += valoare;
		return copie;
	}

	Room operator++()//operatorul de preincrementare
	{
		this->nrOfSeats++;
		return *this;
	}

	Room operator++(int i)//operatorul de postincrementare
	{
		Room copie = *this;
		this->nrOfSeats++;
		return copie;
	}

	explicit operator int()//operator de cast la int explicit
	{
		return nrOfSeats;
	}

	bool operator!()//operatorul de negatie
	{
		return nrOfSeats > 0;
	}

	bool operator<(Room r)//operator conditional
	{
		return this->nrOfSeats < r.nrOfSeats;
	}

	void setTickets() {
		if (movie != nullptr) {
			for (int i = 0; i < movie->getSchedule()->getHourSize(); i++) {
				std::vector<Ticket> t;
				for (int j = 0; j < nrOfSeats; j++) {
					t.push_back(*(new Ticket(this->roomName, j, movie->getMovieName(), movie->getSchedule()->getHours()[i], movie->getPrice())));
				}
				tickets.push_back(t);
			}
		}
		else {
			cout << "Tickets cannot be generated. No movie assigned to this room" << endl;
		}
	}

	friend ostream& operator<<(ostream&, Room&);
	friend istream& operator>>(istream&, Room&);
};

class Cinema {
private:
	std::vector<Movie> movies;
	std::vector<Room> rooms;
public:
	Cinema(const std::vector<Movie>& movies, const std::vector<Room>& rooms) {
		this->movies = movies;
		this->rooms = rooms;
	}
	Room* getRoomById(int id) {
		for (std::vector<Room>::iterator it = rooms.begin(); it < rooms.end(); it++) {
			if (it->getRoomId() == id) {
				return &(*it);
			}
		}
	}

	void showMovies() {
		cout << "=================================== Movie List ""===================================" << endl << endl;
		for (std::vector<Movie>::iterator it = movies.begin(); it < movies.end(); it++) {
			cout << "=================================== " << it->getMovieId() << ". " << it->getMovieName() << " ===================================" << endl;
			cout << "Price: " << it->getPrice() << "$" << endl;
			if (it->getSchedule() != nullptr) {
				cout << "Room: " << getRoomById(it->getSchedule()->getRoomId())->getRoomName() << endl;
				cout << *(it->getSchedule());
			}
			else {
				cout << "No schedule set yet!" << endl;
			}
		}
		cout << "============================================================" << endl;
	}

	void showAvailableMovies() {
		cout << "===================== Available Movies ===========================" << endl;
		for (std::vector<Movie>::iterator it = movies.begin(); it < movies.end(); it++) {
			if (it->getSchedule() != nullptr)
			{
				cout << it->getMovieId() << ". " << it->getMovieName() << " -> " << "Room: " << getRoomById(it->getSchedule()->getRoomId())->getRoomName() << endl;
			}
		}
	}


	void showAvaibleRooms() {
		cout << "===================== Avaible Rooms ===========================" << endl;
		for (std::vector<Room>::iterator it = rooms.begin(); it < rooms.end(); it++) {
			if (it->getMovie() == nullptr)
			{
				cout << it->getRoomId() << ". " << it->getRoomName() << " -> " << it->getNrOfSeats() << " seats" << endl;
			}
		}
	}


	bool checkIfRoomIsFree(int roomId) {
		if (rooms.size() < roomId) {
			cout << "This room is not available" << endl << "Enter other roomId: ";
			return false;
		}
		else {
			for (std::vector<Room>::iterator it = rooms.begin(); it < rooms.end(); it++) {
				if (it->getRoomId() == roomId) {
					if (it->getMovie() != nullptr) {
						cout << "This room is bussy" << endl << "Enter other roomId: ";
						return false;
					}
				}
			}
		}
		return true;
	}

	void setMovieSchedule(int movieId)
	{
		showAvaibleRooms();
		cout << "Enter roomId: ";
		int roomId;
		cin >> roomId;
		while (!checkIfRoomIsFree(roomId)) {
			cin >> roomId;
		}
		cout << "RoomId is set to: " << roomId << endl;
		int input;
		int* hours = nullptr;
		cout << "Enter schedule size: ";
		cin >> input;
		if (input > 0) {
			hours = new int[input];
			for (int i = 0; i < input; i++) {
				cout << "Hour " << i + 1 << ": ";
				int hour;
				cin >> hour;
				hours[i] = hour;
				for (int j = 0; j < i; j++) {
					if (hours[j] == hour) {
						cout << "This hour is already set" << endl; // DE REVENIT AICI 
						i--;
					}
					else {
						hours[i] = hour;
					}
				}
			}
			Schedule* schedule = new Schedule(hours, input, roomId);
			Movie* film = nullptr;
			for (std::vector<Movie>::iterator movieIter = movies.begin(); movieIter < movies.end(); movieIter++) {
				if (movieIter->getMovieId() == movieId) {
					movieIter->setSchedule(schedule);
					for (std::vector<Room>::iterator roomIter = rooms.begin(); roomIter < rooms.end(); roomIter++) {
						if (roomIter->getRoomId() == roomId) {
							roomIter->setMovie(&(*movieIter));
							roomIter->setTickets();
						}
					}
					break;
				}
			}
		}
		else {
			cout << "Size must be bigger than 0" << endl;
		}
		if (hours != nullptr) {
			delete[] hours;
		}
	}

	void addMovie(const Movie& movie) {
		movies.push_back(movie);
	}

	void addRoom(const Room& room) {
		rooms.push_back(room);
	}

	void removeMovie() {
		showMovies();
		cout << "Enter movieId to be removed: ";
		int val;
		cin >> val;
		for (std::vector<Movie>::iterator movieIter = movies.begin(); movieIter < movies.end(); movieIter++) {
			if (movieIter->getMovieId() == val) {
				if (movieIter->getSchedule() != nullptr) {
					if (movieIter->getSchedule()->getRoomId() != -1) {
						for (std::vector<Room>::iterator roomIter = rooms.begin(); roomIter < rooms.end(); roomIter++) {
							if (roomIter->getRoomId() == movieIter->getSchedule()->getRoomId()) {
								roomIter->setMovie(nullptr);
							}
						}
					}
				}
				movies.erase(movieIter);
				cout << "Movie erased successfully" << endl;;
				break;
			}
		}
	}

	void removeRoom() {
		showAvaibleRooms();
		cout << "Enter roomId to be removed: " << endl;
		int val;
		cin >> val;
		for (std::vector<Room>::iterator it = rooms.begin(); it < rooms.end(); it++) {
			if (it->getRoomId() == val) {

			}
		}
	}

	void movieManager() {
		int input = -1;
		while (input != 0) {
			showMovies();
			cout << "1. Add movie" << endl;
			cout << "2. Remove movie" << endl;
			cin >> input;
			Movie* movie = nullptr;
			switch (input)
			{
			case 1:
				movie = new Movie();
				cin >> *movie;
				addMovie(*movie);
				//delete movie;
				break;
			case 2:
				removeMovie();
			default:
				break;
			}
		}

	}

	void scheduleManager() {
		if (movies.size() > 0)
		{
			int input = -1;
			while (input != 0)
			{
				cout << "1. Add schedule" << endl;
				cin >> input;

				switch (input)
				{
				case 1:
					showMovies();
					cout << "Enter movie id: " << endl;
					cin >> input;
					setMovieSchedule(input);

					break;

				default:
					break;
				}
			}
		}
		else {
			cout << "No movies available" << endl << endl;
		}
	}

	void roomsManager() {
		int input = -1;
		while (input != 0) {
			cout << endl << "1. Add room" << endl;
			cin >> input;
			Room* room = nullptr;
			string roomName = {};
			switch (input)
			{
			case 1:
				cout << "Enter room name: ";
				cin >> roomName;
				cout << "Enter number of seats: ";
				int nrOfSeats;
				cin >> nrOfSeats;
				room = new Room(roomName.c_str(), nrOfSeats);
				addRoom(*room);
				//delete movie;
				break;
			default:
				break;
			}
		}
	}

	void reserveTicket(int hourId, int ticketNr, int movieId) {
		for (std::vector<Room>::iterator roomsIter = rooms.begin(); roomsIter < rooms.end(); roomsIter++) {
			if (movieId == roomsIter->getMovie()->getMovieId()) {
				std::vector<Ticket>& tickets = roomsIter->getSeatsByHourId(hourId);
				if (tickets[ticketNr].getIsAvailable())
				{
					tickets[ticketNr].setIsAvailable(false);
					cout << "Ticket reserved!!!" << endl << endl;
					cout << tickets[ticketNr];
					std::stringstream ss;

					ss << "Ticket_" << ticketNr + 1 << ".txt";

					std::ofstream fout(ss.str().c_str());

					fout << tickets[ticketNr];
				}
				else {
					cout << "Seat is not available" << endl;
				}
			}
		}
	}

	void reserveSeatByHourId(int movieId, int hourId) {
		cout << "===========================================================" << endl;
		cout << "===========================================================" << endl;
		for (std::vector<Room>::iterator roomsIter = rooms.begin(); roomsIter < rooms.end(); roomsIter++) {
			if (movieId == roomsIter->getMovie()->getMovieId()) {
				std::vector<Ticket>& tickets = roomsIter->getSeatsByHourId(hourId);
				int i = 0;
				for (std::vector<Ticket>::iterator ticketsIter = tickets.begin(); ticketsIter < tickets.end(); ticketsIter++) {
					if (i % 10 == 0) {
						cout << endl;
					}
					cout << ticketsIter->getseatNr() + 1 << " ";
					i++;
				}
				cout << endl << endl;


				int ticketNr = -1;
				while (ticketNr != 0) {
					cout << "Reserve ticket number: ";
					cin >> ticketNr;
					ticketNr--;
					if (ticketNr > 0) {
						reserveTicket(hourId, ticketNr, movieId);
					}
					ticketNr++;
				}
			}
		}
	}

	void reserveSeats(int movieId) {

		for (std::vector<Movie>::iterator it = movies.begin(); it < movies.end(); it++) {
			if (it->getMovieId() == movieId) {
				cout << *(it->getSchedule()) << endl;
				int input = -1;
				cout << "Enter hour id: ";
				cin >> input;
				input--;
				if (input < it->getSchedule()->getHourSize()) {
					reserveSeatByHourId(movieId, input);
				}
				else {
					cout << "Invalid input. Try again!" << endl;
				}
			}
		}
	}

	void isTicketFree(int id) {

	}

	void start() {
		cout << "Press always 0 to back to the previous menu" << endl;
		while (true) {
			cout << "Choose one option: " << endl;
			cout << "1. Show movie list" << endl;
			cout << "2. Manage Cinema" << endl;
			int input;
			cin >> input;
			switch (input)
			{
			case 1:
				while (input != 0) {
					showAvailableMovies();
					cout << "Enter movie id: ";
					cin >> input;
					if (input != 0) {
						reserveSeats(input);
					}
				}
				break;
			case 2:
				while (input != 0) {
					cout << "1. Manage Movies" << endl;
					cout << "2. Manage Schedule" << endl;
					cout << "3. Manage Rooms" << endl;
					cin >> input;
					switch (input)
					{
					case 1:
						movieManager();
						break;
					case 2:
						scheduleManager();
						break;
					case 3:
						roomsManager();
						break;
					default:
						break;
					}
				}

				break;
			default:
				cout << "Not a valid input. Try again" << endl;
				break;
			}
		}
	}


};


ostream& operator<<(ostream& out, Schedule& s)
{
	if (&s != nullptr)
		for (int i = 0; i < s.hoursSize; i++)
			out << i + 1 << ". Hour: " << s.hours[i] << endl;
	else
		out << "No schedule set yet" << endl;
	return out;
}


ostream& operator<<(ostream& out, Movie& f)
{
	out << "Movie name: ";
	if (f.movieName != nullptr)
	{
		out << f.movieName << endl;
	}
	out << "Movie genre: " << f.genre << endl;
	out << "Movie length(minutes): " << f.length << endl;
	out << "Movie Price ($): " << f.price << endl;
	if (f.schedule != nullptr)
	{
		out << *f.schedule << endl;
	}
	out << "*************************************" << endl;
	return out;
}

istream& operator>>(istream& in, Movie& f)
{
	char buffer[100];
	cout << "Enter movie name: ";
	in >> ws;
	in.getline(buffer, 99);
	if (f.movieName != nullptr)
	{
		delete[] f.movieName;
	}
	f.movieName = new char[strlen(buffer) + 1];
	strcpy_s(f.movieName, strlen(buffer) + 1, buffer);
	cout << "Enter movie genre: ";
	in >> f.genre;
	cout << "Enter movie length(minutes): ";
	in >> f.length;
	cout << "Enter movie price($): ";
	in >> f.price;
	return in;
}

ostream& operator<<(ostream& out, Room r)
{
	out << "Room id: " << r.getRoomId() << endl;
	out << "Room name: ";
	if (r.getRoomName() != nullptr)
	{
		out << r.getRoomName();
	}
	out << endl;
	out << "Seats number: " << r.getNrOfSeats() << endl;
	out << "Seats: ";
	for (int i = 0; i < r.getNrOfSeats(); i++)
	{
		//out << r.getSeats()[i] << " ";
	}
	out << endl;
	return out;
}

istream& operator>>(istream& in, Room& r)
{
	cout << "Enter data for room id " << r.roomId << endl;
	string buffer;
	cout << "Enter room name: ";
	in >> buffer;
	if (r.roomName != nullptr)
	{
		delete[] r.roomName;
	}
	r.roomName = new char[buffer.length() + 1];
	strcpy_s(r.roomName, buffer.length() + 1, buffer.c_str());
	cout << "Enter number of seats:";
	in >> r.nrOfSeats;
	r.nrOfSeats = 0;
	return in;

};

ostream& operator<<(ostream& out, Ticket &t)
{
	out << "Room name: ";
	if (t.roomName != nullptr)
	{
		out << t.roomName;
	}
	out << endl;
	out << "Seat nr: " << t.seatNr + 1 << endl;
	out << "Movie name: ";
	if (t.movieName != nullptr)
	{
		out << t.movieName;
	}
	out << endl;
	out << "Hour: " << t.hour << endl;
	out << "Price($): " << t.price << endl;

	return out;
}

istream& operator>>(istream& in, Ticket& t)
{
	string buffer;
	cout << "Enter room name: ";
	in >> buffer;
	if (t.roomName != nullptr)
	{
		delete[] t.roomName;
	}
	t.roomName = new char[buffer.length() + 1];
	strcpy_s(t.roomName, buffer.length() + 1, buffer.c_str());
	cout << "Enter seat nr:";
	in >> t.seatNr;
	string buffer1;
	cout << "Enter movie name: ";
	in >> buffer1;
	if (t.movieName != nullptr)
	{
		delete[] t.movieName;
	}
	t.movieName = new char[buffer1.length() + 1];
	strcpy_s(t.movieName, buffer1.length() + 1, buffer1.c_str());
	cout << "Enter hour: ";
	in >> t.hour;
	cout << "Enter price:";
	in >> t.price;

	return in;
}

int Movie::counter = 1;
int Room::counter = 1;


int main()
{
	Cinema cinema({}, {});
	cinema.start();
}