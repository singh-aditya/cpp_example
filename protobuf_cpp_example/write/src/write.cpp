#include <iostream>
#include <fstream>
#include <string>
#include <google/protobuf/util/json_util.h>

#include "addressbook.pb.h"

using namespace std;

// This function fills in a Person message based on user input.
void PromptForAddress(example::Person* person) {
	cout << "Enter person ID number: ";
	int id;
	cin >> id;
	person->set_id(id);
	cin.ignore(256, '\n');

	cout << "Enter name: ";
	getline(cin, *person->mutable_name());

	cout << "Enter email address (blank for none): ";
	string email;
	getline(cin, email);
	if (!email.empty()) {
		person->set_email(email);
	}

	while (true) {
		cout << "Enter a phone number (or leave blank to finish): ";
		string number;
		getline(cin, number);
		if (number.empty()) {
			break;
		}

		example::Person::PhoneNumber* phone_number = person->add_phones();
		phone_number->set_number(number);

		cout << "Is this a mobile, home, or work phone? ";
		string type;
		getline(cin, type);
		if (type == "mobile") {
			phone_number->set_type(example::Person::MOBILE);
		}
		else if (type == "home") {
			phone_number->set_type(example::Person::HOME);
		}
		else if (type == "work") {
			phone_number->set_type(example::Person::WORK);
		}
		else {
			cout << "Unknown phone type.  Using default." << endl;
		}
	}
}

// Main function:  Reads the entire address book from a file,
//   adds one person based on user input, then writes it back out to the same
//   file.
int main(int argc, char* argv[]) {
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	if (argc != 2) {
		cerr << "Usage:  " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
		return -1;
	}

	example::AddressBook address_book;

	{
		// Read the existing address book.
		fstream input(argv[1], ios::in | ios::binary);
		if (!input) {
			cout << argv[1] << ": File not found.  Creating a new file." << endl;
		}
		else if (!address_book.ParseFromIstream(&input)) {
			cerr << "Failed to parse address book." << endl;
			return -1;
		}
	}

	// Add an address.
	PromptForAddress(address_book.add_people());

	{
		// Write the new address book back to disk.
		fstream output(argv[1], ios::out | ios::trunc | ios::binary);
		if (!address_book.SerializeToOstream(&output)) {
			cerr << "Failed to write address book." << endl;
			return -1;
		}
	}

	string json_string;

	// Create a json_string from address_book.
	google::protobuf::util::JsonPrintOptions options;
	options.add_whitespace = true;
	options.always_print_primitive_fields = true;
	options.preserve_proto_field_names = true;
	MessageToJsonString(address_book, &json_string, options);

	// Print json_string.
	cout << "File " << argv[1] << " contents as json:["<< json_string << "]"<< endl;

	// Optional:  Delete all global objects allocated by libprotobuf.
	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}