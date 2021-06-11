#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#define N 100005
using namespace std;

int num, uid, uidq;
double Balance[N];
string username[N];
string password[N];

struct useraccount {
	string username_;
	string password;
};
void import();
void login();
void user_pannel();
void admin_pannel();
bool user_login(string, string);
bool userexists(string);
void creataccount();
void ListUsers();
void DeleteAccount();
void Modify();
void enquiry(int);
void deposit(int);
void withdraw(int);
void export_();
void transfer(int);
bool confirm();
int main() {
	import();
	login();
	return 0;
}

void import() {
	num = 0;
	ifstream import, balance;
	import.open("Userinfo.txt", ios::app);
	balance.open("Balance.txt", ios::app);
	while (true)
	{
		import >> username[num];
		import >> password[num];
		balance >> Balance[num];
		if (import.eof())
			break;
		num++;
	}
}
void login() {

	string usr, pass;
	usr.clear(), pass.clear();
	cout << "Enter your username: ";
	cin >> usr;
	cout << "Enter your password: ";
	cin >> pass;
	if (usr == "Admin") {
		if (pass == "Admin")
			admin_pannel();
		else {
			cout << "Incorrect username or password, try again. \n";
			login();
		}
	}
	else if (user_login(usr, pass))
		user_pannel();
	else {
		cout << "Incorrect username or password, try again. \n";
		login();
	}

}
bool user_login(string usr, string pass) {
	uidq = 0;
	for (int i = 0; i < num; i++)
	{
		uidq++;
		if (username[i] == usr)
		{
			if (password[i] == pass)
				return true;
			else
				return false;
		}
	}
	return false;
}
void admin_pannel() {
	char choice_;
	choice_ = '-1';
	while (choice_ != '6') {
		cout << "Please choose one option." << endl;
		cout << "[1] Create Account." << endl;
		cout << "[2] Modify Account." << endl;
		cout << "[3] Delete Account." << endl;
		cout << "[4] List Accounts." << endl;
		cout << "[5] To Logout." << endl;
		cout << "[6] To exit the programme." << endl;
		cin >> choice_;
		if (choice_ == '1')
			creataccount();
		else if (choice_ == '2')
			Modify();
		else if (choice_ == '3')
			DeleteAccount();
		else if (choice_ == '4')
			ListUsers();
		else if (choice_ == '5')
		{
			choice_ = 6;
			login();
		}
		else if (choice_ == '6')
			cout << ' ';
		else
			cout << "Invalid, try again." << endl;
	}
}
void user_pannel() {
	char i = '-1';
	while (i != '6') {
		cout << "[1] To inquire." << endl;
		cout << "[2] To make a deposit." << endl;
		cout << "[3] To withdraw." << endl;
		cout << "[4] To transfer." << endl;
		cout << "[5] To Logout" << endl;
		cout << "[6] To exit the programme." << endl;
		cin >> i;
		if (i == '1')
			enquiry(uidq - 1);
		else if (i == '2')
			deposit(uidq - 1);
		else if (i == '3')
			withdraw(uidq - 1);
		else if (i == '4')
			transfer(uidq - 1);
		else if (i == '5') {
			i = 6;
			login();
		}
		else if (i == '6')
			cout << ' ';
		else
			cout << "Invalid, try again." << endl;
	}
}
bool userexists(string username_) {  //check if the username already exist  
	uid = -1; //flag the index of the user for an Admin or for transactins.
	for (int i = 0; i < num; i++)
	{
		uid++;//To know the user ID you're modifying
		if (username_ == username[i])
			return true;
	}
	uid = -1;
	return false;
}
void creataccount() {
	useraccount user;
	string newpassword;

	cout << "Please enter a username: ";
	cin >> user.username_;   //user enter his username
	int y = -2;   //to prevent reptition of functions 
	if (userexists(user.username_)) {
		cout << "User name already exists." << endl << "Enter another one: ";
		creataccount();
	}
	else if (y == -2) {

		cout << "please enter a password: ";
		cin >> user.password;
		cout << "Confirm passowrd: ";
		cin >> newpassword;
		if (newpassword != user.password) {  // to check if the password and confirm password match
			cout << "Passwords do not match, try again." << endl;
			creataccount();
		}
		else {
			username[num] = user.username_;
			password[num] = user.password;
			Balance[num] = 0;
			++num;//Number of users registered in the system.
			export_();
			y = 1;       //we changed the y so he doesnt enter the if condition again
		}
	}
}
void ListUsers() {  //to display or list all the users
	if (num == 0)
		cout << "There is currently no users available.";
	else {
		cout << "Existing users are:\n";
		for (int i = 0; i < num; i++) // loop on the array to display existing users.
		{
			cout << "- " << username[i] << endl;
		}
	}
	cout << endl;

}
void DeleteAccount() {
	string key; //the username to be deleted.
	cout << "Enter the account username you wish to delete: ";
	cin >> key;
	if (userexists(key)) {
		if (confirm()) {
			if (uid == num - 1) { //If the meant one is the last user name.
				username[uid].clear();
				password[uid].clear();
				Balance[uid] = NULL;
				num -= 1;
			}
			else { //To shift the accounts and delete the meant user.
				for (int i = uid; i < num; i++)
				{
					username[i] = username[i + 1];
					password[i] = password[i + 1];
					Balance[i] = Balance[i + 1];
				}
				num -= 1;
			}
			cout << "Account Deleted Successfully.\n";
			export_();
		}
		else {
			admin_pannel();
		}
	}
	else {
		cout << "The username does not exist" << endl << "Enter another one" << endl;
		DeleteAccount();
	}
}
void Modify() {
	string key;//the account username you wish to modify
	string d;//variable for writing into files.
	string newsave;//the new username or password.
	cout << "Enter the account username you wish to modify:" << endl;
	cin >> key;
	if (userexists(key)) {
		string saved;
		int choice;// to choose between username or password change.
		cout << "What do you wish to modify?" << endl << "[1] for username" << endl << "[2] for password" << endl;
		cin >> choice;
		if (choice == 1) {
			cout << "Enter new username: ";
			cin >> newsave;//Enter the new username
			if (confirm()) {
				username[uid] = newsave;
				export_();
			}
			else { admin_pannel(); }
		}
		else if (choice == 2) {//Enter the new password
			cout << "Enter new password: ";
			cin >> newsave;
			if (confirm()) {
				password[uid] = newsave;
				export_();
			}
			else { admin_pannel(); }
		}
		else {//the input is not a choice.
			cout << "Thats not a valid input" << endl;
			Modify();
		}
	}
	else {
		cout << "The username does not exist" << endl << "Enter another one" << endl;
		Modify();
	}
}
void enquiry(int id_) {
	cout << fixed;
	cout << setprecision(2);
	cout << "Your balance is: " << Balance[id_] << endl;
}
void deposit(int id_) {
	double add;
	cout << "Enter the amount you want to deposit: ";
	cin >> add;
	if (confirm()) {
		Balance[id_] += add;
		export_();
	}
	else { user_pannel(); }

}
void withdraw(int id_) {
	double sub;
	cout << "Enter the amount you want to withdraw: ";
	cin >> sub;
	if (sub > Balance[id_]) {
		cout << "Insufficient balance. Try again" << endl;
		withdraw(id_);
	}
	else {
		if (confirm()) {
			Balance[id_] = Balance[id_] - sub;
			export_();
		}
		else { user_pannel(); }
	}
}
void transfer(int uids_) {
	double amount = 0;
	string str;
	cout << "Enter the username you want to transfer money to: ";
	cin >> str;
	if (userexists(str)) {
		cout << "Enter the amount of money to be transfered: ";
		cin >> amount;
		if (amount > Balance[uids_]) {
			cout << "Insufficient balance. Try again" << endl;
			transfer(uids_);
		}
		else {
			if (confirm())
			{
				Balance[uids_] -= amount;
				Balance[uid] += amount;
				export_();
			}
			else { user_pannel(); }
		}
	}
	else {
		cout << "Incorrect username, try again." << endl;
		transfer(uids_);
	}

}
void export_() {
	ofstream export_, balance;
	export_.open("Userinfo.txt", std::ofstream::out | ofstream::trunc);
	balance.open("Balance.txt", std::ofstream::out | ofstream::trunc);
	for (int i = 0; i < num; i++)
	{
		export_ << username[i] << endl;
		export_ << password[i] << endl;
		balance << Balance[i] << endl;
	}
}
bool confirm()
{
	char input;
	cout << "[1]  To Confirm\n[2]  To Cancel\n";
	cin >> input;
	if (input == '1') {
		cout << "Confirmed\n";
		return true;
	}
	else if (input == '2') {
		cout << "Cancelled\n";
		return false;
	}
	else { confirm(); }
}
