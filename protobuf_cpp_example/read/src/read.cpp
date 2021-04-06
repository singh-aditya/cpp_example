// See README.txt for information and build instructions.

#include <fstream>
#include <google/protobuf/util/time_util.h>
#include <iostream>
#include <string>
#include <google/protobuf/util/json_util.h>

#include "addressbook.pb.h"

using namespace std;

using google::protobuf::util::TimeUtil;

// Iterates though all people in the AddressBook and prints info about them.
void ListPeople(const example::AddressBook& address_book) {
  for (int i = 0; i < address_book.people_size(); i++) {
    const example::Person& person = address_book.people(i);

    cout << "Person ID: " << person.id() << endl;
    cout << "  Name: " << person.name() << endl;
    if (person.email() != "") {
      cout << "  E-mail address: " << person.email() << endl;
    }

    for (int j = 0; j < person.phones_size(); j++) {
      const example::Person::PhoneNumber& phone_number = person.phones(j);

      switch (phone_number.type()) {
        case example::Person::MOBILE:
          cout << "  Mobile phone #: ";
          break;
        case example::Person::HOME:
          cout << "  Home phone #: ";
          break;
        case example::Person::WORK:
          cout << "  Work phone #: ";
          break;
        default:
          cout << "  Unknown phone #: ";
          break;
      }
      cout << phone_number.number() << endl;
    }
    if (person.has_last_updated()) {
      cout << "  Updated: " << TimeUtil::ToString(person.last_updated()) << endl;
    }
  }
}

// Main function:  Reads the entire address book from a file and prints all
//   the information inside.
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
    if (!address_book.ParseFromIstream(&input)) {
      cerr << "Failed to parse address book." << endl;
      return -1;
    }
  }

  ListPeople(address_book);

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
