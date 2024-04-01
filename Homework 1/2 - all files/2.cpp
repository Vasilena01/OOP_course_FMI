// Homework 1
// Vasilena Stanoyska
// fn: 4MI0600290
// Zad 2

#include <iostream>
#include <fstream>
#include <sstream>
#pragma warning (disable : 4996)

namespace GlobalConstants
{
	constexpr size_t MAX_PLAYLIST_LENGTH = 30;
	constexpr size_t MAX_SONG_NAME_LENGTH = 64;
	constexpr size_t MAX_GENRE_NAME = 64;
	constexpr size_t MAX_CONTENT_SIZE = 256;
	int HOUR_IN_SECONDS = 3600;
	int MIN_IN_SECONDS = 60;
}

int getFileSize(std::ifstream& file)
{
	int currPos = file.tellg();
	file.seekg(0, std::ios::end);
	int size = file.tellg();
	file.seekg(currPos);

	return size;
}

int convertDurationInSeconds(int hours, int minutes, int seconds)
{
	int duration = 0;

	duration = hours * GlobalConstants::HOUR_IN_SECONDS + minutes * GlobalConstants::MIN_IN_SECONDS + seconds;
	return duration;
}

void printBit(char ch)
{
	for (int i = 7; i >= 0; --i) {
		std::cout << ((ch >> i) & 1);
	}
	std::cout << std::endl;
}

// CLASS SONG
class Song
{
private:
	char name[GlobalConstants::MAX_SONG_NAME_LENGTH];
	int duration;
	char genre;
	char content[GlobalConstants::MAX_CONTENT_SIZE];
public:
	// Default constructor
	Song() {
		// Initialize member variables to default values
		strcpy(this->name, "");
		this->duration = 0;
		this->genre = 0;
		strcpy(this->content, "");
	}

	Song(const char* name, int hours, int minutes, int seconds, const char* genre, const char* fileName) {
		strcpy(this->name, name);
		this->duration = convertDurationInSeconds(hours, minutes, seconds);
		this->genre = getEncodedGenre(genre);
		strcpy(this->content, getSongContentFromFile(fileName));
	}

	const char* getName() const;

	int getDuration() const;

	const char* getGenreName(int index) const;

	const char* getDecodedGenre(char genreCh) const;

	char* getSongContent();

	void setName(const char* newName);

	void setContent(const char* newContent);

	int getCharIndex(char genreChar) const;

	char getEncodedGenre(const char* genre) const;

	void printDecodedGenre(char genre);

	bool compareGenres(const char* comparingGenre);

	void printSongDuration(int duration);

	char* getSongContentFromFile(const char* fileName) const;

	void printSong();
};

const char* Song::getName() const
{
	return this->name;
}

int Song::getDuration() const
{
	return this->duration;
}

const char* Song::getGenreName(int index) const
{
	switch (index)
	{
	case 0: return "Rock"; break;
	case 1: return "Pop"; break;
	case 2: return "HipHop"; break;
	case 3: return "Electronic"; break;
	case 4: return "Jazz"; break;
	default: return "None";
	}
}

const char* Song::getDecodedGenre(char genreCh) const
{
	int mask = 1;
	const char* genre = nullptr;
	for (int i = 0; i < 5; i++)
	{
		if (mask & genreCh)
		{
			genre = getGenreName(i);
		}
		mask <<= 1;
	}

	return genre;
}

char* Song::getSongContent()
{
	return this->content;
}

void Song::setName(const char* newName)
{
	strcpy(this->name, newName);
}

void Song::setContent(const char* newContent)
{
	strcpy(this->content, newContent);
}

int Song::getCharIndex(char genreChar) const
{
	switch (genreChar)
	{
	case 'r': return 0;
	case 'p': return 1;
	case 'h': return 2;
	case 'e': return 3;
	case 'j': return 4;
	default: return -1;
	}
}

char Song::getEncodedGenre(const char* genre) const
{
	if (!genre)
		return '0';

	char genreIndex = 0;
	while (*genre)
	{
		genreIndex |= (1 << getCharIndex(*genre));
		genre++;
	}

	return genreIndex;
}

void Song::printDecodedGenre(char genre)
{
	int mask = 1;
	bool isFirstGenre = true;
	for (int i = 0; i < 5; i++)
	{
		if (mask & genre)
		{
			std::cout << (isFirstGenre ? "" : "&");
			isFirstGenre = false;
			std::cout << getGenreName(i);
		}
		mask <<= 1;
	}
}

bool Song::compareGenres(const char* comparingGenre)
{
	int mask = 1;
	bool isFirstGenre = true;
	char currGenre[GlobalConstants::MAX_GENRE_NAME] = "";

	for (int i = 0; i < 5; i++)
	{
		if (mask & genre)
		{
			isFirstGenre = false;
			strcpy(currGenre, getGenreName(i));
		}
		mask <<= 1;

		if (currGenre && strcmp(comparingGenre, currGenre) == 0)
			return true;
	}

	return false;
}

void Song::printSongDuration(int duration)
{
	int hours = duration / GlobalConstants::HOUR_IN_SECONDS;
	int minutes = (duration % GlobalConstants::HOUR_IN_SECONDS) / GlobalConstants::MIN_IN_SECONDS;
	int seconds = duration % GlobalConstants::MIN_IN_SECONDS;

	if (hours <= 9)
		std::cout << "0" << hours << ":";
	else
		std::cout << hours << ":";

	if (minutes <= 9)
		std::cout << "0" << minutes << ":";
	else
		std::cout << minutes << ":";

	if (seconds <= 9)
		std::cout << "0" << seconds << ", ";
	else
		std::cout << seconds << ", ";
}

char* Song::getSongContentFromFile(const char* fileName) const
{
	if (!fileName)
		return nullptr;

	std::ifstream file(fileName, std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Failed to open content file!";
		return nullptr;
	}

	char buff[GlobalConstants::MAX_CONTENT_SIZE];
	int fileSize = getFileSize(file);

	file.read((char*)buff, fileSize);
	buff[fileSize] = '\0';

	return buff;
}

void Song::printSong()
{
	std::cout << this->name << ", ";
	printSongDuration(this->duration);
	printDecodedGenre(this->genre);
}

// CLASS PLAYLIST
class Playlist
{
private:
	int songsCount;
	Song songs[GlobalConstants::MAX_PLAYLIST_LENGTH];
public:
	Playlist()
	{
		this->songsCount = 0;
		for (int i = 0; i < GlobalConstants::MAX_PLAYLIST_LENGTH; ++i) {
			this->songs[i] = Song();
		}
	}

	void addSong(const char* name, int hours, int minutes, int seconds,
		const char* genre, const char* fileName);

	void sortByName();

	void sortByDuration();

	Song getSongByName(const char* songName);

	int getSongIndex(const char* songName);

	void getSongsByGenre(const char* genre);

	void printSongByName(const char* songName);

	void editPlaylistByName(const char* currSongName, const char* newSongName);

	void saveSongInFile(const char* songName, const char* fileName);

	void modifySongContent(const char* songName, int position);

	void mixSongs(const char* songName1, const char* songName2);

	void printSongs();
};

void Playlist::addSong(const char* name, int hours, int minutes, int seconds,
	const char* genre, const char* fileName)
{
	Song song(name, hours, minutes, seconds, genre, fileName);
	this->songs[this->songsCount++] = song;
}

void Playlist::sortByName()
{
	// Selection sort
	Song song;
	for (int i = 0; i < this->songsCount - 1; i++)
	{
		int minIndex = i;

		for (int j = i + 1; j < this->songsCount; j++)
		{
			if (strcmp(this->songs[j].getName(), this->songs[minIndex].getName()) < 0)
				minIndex = j;
		}

		if (minIndex != i)
			std::swap(this->songs[i], this->songs[minIndex]);
	}
}

void Playlist::sortByDuration()
{
	// Selection sort
	Song song;
	for (int i = 0; i < this->songsCount - 1; i++)
	{
		int minIndex = i;

		for (int j = i + 1; j < this->songsCount; j++)
		{
			if (this->songs[j].getDuration() < this->songs[minIndex].getDuration())
				minIndex = j;
		}

		if (minIndex != i)
			std::swap(this->songs[i], this->songs[minIndex]);
	}
}

Song Playlist::getSongByName(const char* songName)
{
	if (!songName)
		return {};

	for (int i = 0; i < this->songsCount; i++)
	{

		if (strcmp(this->songs[i].getName(), songName) == 0)
		{
			Song song = this->songs[i];
			return song;
		}
	}

	std::cout << "The playlist not contains a song with the name: " << songName;
	return {};
}

int Playlist::getSongIndex(const char* songName)
{
	if (!songName)
		return -1;

	for (int i = 0; i < this->songsCount; i++)
	{

		if (strcmp(this->songs[i].getName(), songName) == 0)
			return i;
	}

	std::cout << "The playlist not contains a song with the name: " << songName;
	return -1;
}

void Playlist::getSongsByGenre(const char* genre)
{
	if (!genre)
		return;

	Song song;
	char encodedGenre = song.getEncodedGenre(genre);
	const char* sortingGenre = song.getDecodedGenre(encodedGenre);

	if (!sortingGenre)
		return;

	for (int i = 0; i < this->songsCount; i++)
	{

		if (this->songs[i].compareGenres(sortingGenre))
		{
			this->songs[i].printSong();
			std::cout << std::endl;
		}
	}
}

void Playlist::printSongByName(const char* songName)
{
	Song song = getSongByName(songName);
	if (strcmp(song.getName(), "\0") == 0)
	{
		std::cout << "The playlist not contains a song with the name: " << songName << "so this song can't be printed!";
		return;
	}

	for (int i = 0; i < this->songsCount; i++)
	{
		if (strcmp(song.getName(), this->songs[i].getName()) == 0)
		{
			song.printSong();
			std::cout << std::endl;
		}
	}
}

void Playlist::editPlaylistByName(const char* currSongName, const char* newSongName)
{
	int songIndex = getSongIndex(currSongName);
	Song song = getSongByName(currSongName);

	if (song.getName() == "\0")
		return;

	this->songs[songIndex].setName(newSongName);
}

void Playlist::saveSongInFile(const char* songName, const char* fileName)
{
	std::ofstream file(fileName, std::ios::binary);

	if (!file.is_open())
	{
		std::cerr << "Fail to open file!";
		return;
	}

	Song song = getSongByName(songName);
	if (song.getName() == "\0")
		return;

	file.write((const char*)song.getSongContent(), strlen(song.getSongContent()));
}

void Playlist::modifySongContent(const char* songName, int position)
{
	Song song = getSongByName(songName);
	int index = getSongIndex(songName);

	if (song.getName() == "\0")
		return;

	char* content = song.getSongContent();

	if (!content)
		return;

	int totalBitsToShift = position - 1;
	int currIndex = strlen(content) - 1;

	while (currIndex >= 0)
	{
		int mask = 1;

		if (totalBitsToShift > 7)
		{
			currIndex--;
			totalBitsToShift -= 8;
			continue;
		}

		mask <<= totalBitsToShift;
		content[currIndex] |= mask;
		printBit(content[currIndex]);
		totalBitsToShift += position;
	}
	this->songs[index].setContent(content);
}

void Playlist::mixSongs(const char* songName1, const char* songName2)
{
	Song firstSong = getSongByName(songName1);
	int indexFirst = getSongIndex(songName1);
	Song secondSong = getSongByName(songName2);

	if (firstSong.getName() == "\0" || secondSong.getName() == "\0")
		return;

	char* firstContent = firstSong.getSongContent();
	char* secondContent = secondSong.getSongContent();

	if (!firstContent || !secondContent)
		return;

	int firstContLen = strlen(firstContent);
	int secondContLen = strlen(secondContent);

	int index = 0;
	while (firstContLen > 0 && secondContLen > 0)
	{
		firstContent[index++] ^= secondContent[index++];
		firstContLen--;
		secondContLen--;
	}

	this->songs[indexFirst].setContent(firstContent);
}

void Playlist::printSongs()
{
	for (int i = 0; i < this->songsCount; i++)
	{
		this->songs[i].printSong();
		std::cout << std::endl;
	}
}

int main()
{
	// TO TEST ALL FUNCTIONS
	Playlist playlist;

	// Adds a new song to the playlist
	playlist.addSong("Song 2", 0, 1, 55, "rp", "song1.txt");
	playlist.addSong("Song 5", 0, 1, 5, "p", "song2.txt");
	playlist.addSong("Song 3", 1, 1, 5, "j", "song2.txt");

	// Sorts the playlist by name
	//playlist.sortByName();
	
	// Sorts the playlist by duration
	//playlist.sortByDuration();
	
	// Edits the name of a given song, to be set to another name
	//playlist.editPlaylistByName("Song 2", "Song 5");
	
	// Prints a song/songs by it's/theirs name
	//playlist.printSongByName("Song 5");
	
	// Gets a song/songs by it's/theirs genre
	//playlist.getSongsByGenre("p");
	
	// Modifying every k bit of a song's content
	//playlist.modifySongContent("Song 2", 3);
	
	// Mixing song contents
	//playlist.mixSongs("Song 2", "Song 1");
	
	// Saving song content in file
	//playlist.saveSongInFile("Song 2", "savedSong.txt");

	// Printing all songs in playlist
	//playlist.printSongs();
}
