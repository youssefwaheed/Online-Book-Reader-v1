/*
 * Created in Stamper 2022.
 * IN this project, I used some oop and pointers to make every thing connected with each other.
 *
 * Currently, the system has 2 users.
 * admin: username is "admin" password is "123".
 * normal user: username is "youssef" password is "222".
 *
 * I hope there are no bugs or any memory leak.
 *
 * */

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

/*____________________________________________Utility Functions___________________________________________*/

void PrintMenu(const vector<string> &menu){
    int num = 1;
    for (auto &line : menu) {
        cout<<num++<<": " <<line<<"\n";
    }

}

int SelectFromRange(int start,int end){

    cout<<"Enter number in range "<< start << " - " <<end<< "\n";

    int choice;
    cin >> choice;

    if (choice > end || choice < start){
        return SelectFromRange(start,end);
    }

    return choice;
}

/*_________________________________________________________________________________________________________*/

class User{

private:
    string username;
    string password;
    string name;
    string email;
    bool isAdmin;

    //reading history for book name and the last page user stopped reading in.
    map<string,int> readingHistory;

public:
    User():
        username{},password{},name{},email{},isAdmin(false){
    }

    User(const string& username,const string& password,const string& name,const string& email):
        username(username),password(password),name(name),email(email),isAdmin(false){
    }

    void SetUsername(const string &username) {
        this->username = username;
    }

    void SetPassword(const string &password) {
        this->password = password;
    }

    void SetName(const string &name) {
        this->name = name;
    }

    void SetEmail(const string &email) {
        this->email = email;
    }

    void SetIsAdmin(bool isAdmin) {
        this->isAdmin = isAdmin;
    }

    const string& GetUserName() const{
        return username;
    }

    const string& GetPassword() const{
        return password;
    }

    const string& GetName() const{
        return name;
    }

    const string& GetEmail() const{
        return email;
    }

    bool GetIsAdmin() const{
        return isAdmin;
    }

    inline void Print() const{
        cout << "Name: " << GetName() << "\n" << "Email: " << GetEmail() << "\n" << "UserName: " << GetUserName() << "\n";
    }

    void ReadUserInfo(){

        cout << "Enter password (No Spaces): ";
        cin >> password;

        cout << "Enter name (No Spaces): ";
        cin >> name;

        cout << "Enter email (No Spaces): ";
        cin >> email;

    }

    const map<string,int>& GetReadingHistory() const{
        return readingHistory;
    }

    void SetReadingHistory(const string& bookName , int last) {
        readingHistory[bookName] = last;
    }

};

class Book{
private:
    string bookName;
    string author;

    int numberOfPages;

    vector<string> bookPagesNames;

public:
    const string &GetBookName() const {
        return bookName;
    }

    const string &GetAuthor() const {
        return author;
    }

    int GetNumberOfPages() const {
        return numberOfPages;
    }

    const vector<string> &GetBookPagesNames() const {
        return bookPagesNames;
    }

    void SetBookName(const string &bookName) {
        this->bookName = bookName;
    }

    void SetAuthor(const string &author) {
        this->author = author;
    }

    void SetNumberOfPages(int numberOfPages) {
        this->numberOfPages = numberOfPages;
    }

    void SetBookPagesNames(int numberOfPages) {

        for (int page = 0; page < numberOfPages ; ++page) {
            cout<<"Enter page "<<(page+1)<<" name :";

            string name;
            cin>>name;

            bookPagesNames.push_back(name);
        }

    }

    void SetBookPagesNames(const vector<string> & names) {

        for (int page = 0; page < numberOfPages ; ++page) {
            bookPagesNames.push_back(names[page]);
        }

    }

    void ReadBookInfo(){
        cout << "Enter book name (no spaces): ";
        cin>>bookName;

        cout << "Enter book author (no spaces): ";
        cin>>author;

        cout << "Enter number of pages (no spaces): ";
        cin>>numberOfPages;

        SetBookPagesNames(numberOfPages);

    }

    void Print() const{
        cout << "Book name: "<<GetBookName() << "\nBook author: " <<GetAuthor()<<"\nBook pages names: \n";

        for (int page = 0; page < GetNumberOfPages() ; ++page) {
            cout<<"\tPage "<<(page+1)<<": "<<bookPagesNames[page]<<"\n";
        }
    }

};

class Session{
private:
    int startPage;
    int endPage;
    int currentPage;

    vector<string> menu = {"Next Page","Previous Page","Stop Reading"};
public:
    Session(int startPage,int endPage,int currentPage):
             startPage(startPage),endPage(endPage),currentPage(currentPage){
    }

    bool HasNext() const{
        return (GetCurrentPage() < endPage);
    }

    bool HasPrevious() const{
        return (startPage < GetCurrentPage());
    }

    int GetCurrentPage() const{
        return currentPage;
    }

    void SetCurrentPage(int current){
        currentPage = current;
    }

    void PrintMenu() const{
        ::PrintMenu(menu);
    }

    void StartSession(const Book* const &book){

         const vector<string>& pages = book->GetBookPagesNames();

        cout<<"Current Page: "<<GetCurrentPage()<<"/"<<endPage<<"\n";
        cout <<pages[GetCurrentPage() - 1]<<"\n";

        while(true){
            cout<<endl;
            PrintMenu();

            int choice;
            cin>> choice;

            if(choice == 1){
                if(HasNext()) {
                    SetCurrentPage(GetCurrentPage()+1);
                    cout<<"Current Page: "<<GetCurrentPage()<<"/"<<endPage<<"\n";
                    cout <<pages[GetCurrentPage() - 1]<<"\n";
                }
                else
                    cout<<"No more pages\n";
            }
            else if(choice == 2){
                if(HasPrevious()) {
                    SetCurrentPage(GetCurrentPage()-1);
                    cout<<"Current Page: "<<GetCurrentPage()<<"/"<<endPage<<"\n";
                    cout <<pages[GetCurrentPage() - 1]<<"\n";
                }
                else
                    cout<<"No less pages\n";
            }
            else{
                cout<<"ok!\n";
                break;
            }

        }
    }

};

class BookManger{
private:
    const Book* currentBook;
    vector<Book*> availableBooks;

    void GetAvailableBooks() const{
        int num = 1;
        for (auto &book : availableBooks) {
            cout <<num++<<": "<< book->GetBookName() << "\n";
        }
    }

    int SelectFromAvailableBooks() const{

        cout<<"Select from following: \n";
        GetAvailableBooks();

        int choice;
        cin >> choice;

        return choice;
    }

    void FreeMemory(){
        for (auto book : availableBooks) {
            delete book;
            book = nullptr;
        }
    }

public:
    BookManger (){
        Book* book = new Book;
        book->SetBookName("c++");
        book->SetNumberOfPages(3);
        book->SetBookPagesNames({"c++","oop","ood"});
        availableBooks.emplace_back(book);
    }

    void AddBook(){

        Book* newBook = new Book;
        newBook->ReadBookInfo();

        availableBooks.push_back(newBook);
    }

    void SelectedBook() {
        if(availableBooks.empty()){
            cout<<"No books now\n";
            return;
        }
        SetCurrentBook(availableBooks.at(SelectFromAvailableBooks()-1));
    }

    void SetCurrentBook(const Book* const &book) {
        currentBook = book;
    }

    void SetCurrentBook(const string& bookName) {
        for (auto& book : availableBooks) {
            if(book->GetBookName() == bookName){
                SetCurrentBook(book);
                return;
            }
        }
    }

    const Book* const GetCurrentReadingBook() const{
        return currentBook;
    }

    ~BookManger(){
       FreeMemory();
    }
};

class UserManager{
private:
    User* currentUser;

    map<string,User*> usernameMapUser;

    vector<string> systemMenu = {"Login","Sign Up"};

    void Admin() {
        User* admin = new User("admin","123","youssef","admin@gmail.com");
        admin->SetIsAdmin(true);
        usernameMapUser[admin->GetUserName()] = admin;

        User* user = new User("youssef","222","youssef","youssief@gmail.com");
        usernameMapUser[user->GetUserName()] = user;
    }

    int Login(){
        string username;

        cout<<"Enter Username or -1 to cancel: ";
        cin>>username;

        if(username == "-1")
            return -1;

        if(usernameMapUser.count(username)){

            string password;
            cout<<"Enter password: ";
            cin>>password;

            if(usernameMapUser[username]->GetPassword() == password)
                currentUser = usernameMapUser[username];
            else {
                cout << "Try again\n";
                Login();
            }
            return 1;
        }
        else cout<<"No such user\n";
        return Login();
    }

    void SignUp(){

        string username;
        cout << "Enter UserName or -1 to cancel(No Spaces): \n";
        cin>>username;

        if(username == "-1")
            return;

        if (usernameMapUser.count(username)) {
            cout << "username already exist, try again\n";
            SignUp();
            return;
        }

        User *newUser = new User;

        newUser->SetUsername(username);
        newUser->ReadUserInfo();
        usernameMapUser[newUser->GetUserName()] = newUser;
    }

    void FreeMemory(){
        for (auto user : usernameMapUser) {
            delete user.second;
            user.second = nullptr;
        }
    }

public:

    UserManager(){
        Admin();
    }

    const User* const GetCurrentUser() const{
        return currentUser;
    }

    void AccessSystem(){
        cout<<"Menu:\n";
        PrintMenu(systemMenu);

        int choice = SelectFromRange(1,2);

        if(choice == 1) {
            if(Login() == -1)
                AccessSystem();
            return;
        }
        else{
            SignUp();
            AccessSystem();
        }
    }

    void ListReadingBooks()const{
        const auto list = currentUser->GetReadingHistory();

        int num = 1;
        for (auto &book : list) {
            cout<<num++<<"- "<<book.first<<" "<<book.second<<"\n";
        }
    }

    string SelectFromReadingBooks(){

        if(GetCurrentUser()->GetReadingHistory().empty()) {
            cout << "No History yet.\n";
            return "-1";
        }

        ListReadingBooks();

        int choice;
        cout<<"Select from books: ";
        cin >> choice;

        auto selected = GetCurrentUser()->GetReadingHistory().begin();
        advance(selected,choice-1);

        return selected->first;
    }

    void StartReading(const Book* const &book){

        Session session(1,book->GetNumberOfPages(),currentUser->GetReadingHistory().at(book->GetBookName()));
        session.StartSession(book);
        currentUser->SetReadingHistory(book->GetBookName(), session.GetCurrentPage());

    }

    void AddBookToReadingHistory(const Book* const &book){

        if(!GetCurrentUser()->GetReadingHistory().count(book->GetBookName()))
            currentUser->SetReadingHistory(book->GetBookName(),1);
        else
        {
            cout<<"Book already in your History book\n";
            return;
        }
    }

    ~UserManager(){
       FreeMemory();
    }


};

class OnlineReadingBook{
private:

    BookManger bookManger;
    UserManager userManager;

    vector<string> AdminMenu = {"View profile","Add book","Logout","Close System"};
    vector<string> UserMenu = {"View Profile","List & Select from My Reading History","List & Select from Available Books","Logout","Close System"};

public:

    void Sevice(){
        userManager.AccessSystem();

        if(userManager.GetCurrentUser()->GetIsAdmin()){

            int choice;
            while (true) {
                cout<<endl<<"MENU:\n";
                PrintMenu(AdminMenu);
                cout<<"Select From Menu: ";

                cin>>choice;

                if(choice == 1)
                    userManager.GetCurrentUser()->Print();

                else if(choice == 2)
                    bookManger.AddBook();

                else if(choice == 3 || choice == 4)
                    break;

            }
            if(choice != 4)
                Sevice();
        }

        else {
            int choice;
            while (true) {
                cout<<endl<<"MENU:\n";
                PrintMenu(UserMenu);
                cout<<"Select From Menu: ";


                cin>>choice;

                if(choice == 1)
                    userManager.GetCurrentUser()->Print();

                else if(choice == 2) {
                    string selection = userManager.SelectFromReadingBooks();
                    if( selection == "-1")
                        continue;

                    bookManger.SetCurrentBook(selection);
                    userManager.StartReading(bookManger.GetCurrentReadingBook());

                }

                else if(choice == 3) {

                    bookManger.SelectedBook();
                    userManager.AddBookToReadingHistory(bookManger.GetCurrentReadingBook());
                    userManager.StartReading(bookManger.GetCurrentReadingBook());

                }

                else if(choice == 4 || choice == 5)
                    break;
            }
            if(choice!= 5)
                Sevice();


        }
    }

    ~OnlineReadingBook(){
        cout<<"\n\t\tGood Bye :\")";
    }

};


int main() {

    OnlineReadingBook onlineReadingBook;
    onlineReadingBook.Sevice();

    return 0;
}
