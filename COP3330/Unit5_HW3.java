//Unit5_HW3
//Alexander Gershfeld and Gabriel Perez
//Hatim Boustique
//COP3330
//October 15, 2023

import java.util.Random;
import java.util.Scanner;

public class Driver {
    public static void main(String[] args) {
        BookList Blist = new BookList(); //creates the list for the books to be held

        Scanner input = new Scanner(System.in);

        String bookEntry, bookType, author = null, title = null, isbnStr = null; //information that all books have
        String [] bookInfo;

        System.out.println("Welcome to the book program!");

        //iterates as many times as the user would like, stopping when input is "no"
        while(true) {
            System.out.println("Would you like to create a book object? (yes/no): ");
            String choice = input.nextLine();

            //if the user inputs anything other than yes or no
            while(choice.compareToIgnoreCase("yes") != 0 && choice.compareToIgnoreCase("no") != 0) {
                System.out.println("I'm sorry but " + choice + " isn't a valid answer. Please enter either yes or no: ");
                choice = input.nextLine();
            }

            //if user says yes, goes through the process of adding a book to the list
            if(choice.compareToIgnoreCase("yes") == 0) {
                System.out.println("Please enter the author, title and the isbn of the book separated by /: ");

                //Gets the information for author title and isbn ---------------------------------

                bookEntry = input.nextLine();
                bookInfo = bookEntry.split("/");

                author = bookInfo[0];
                title = bookInfo[1];
                isbnStr = bookInfo[2];

                if(Blist.getBook(isbnStr) != null) {
                    System.out.println("Sorry this ISBN is already taken");
                    continue;
                }

                //--------------------------------------------------------------------------------

                System.out.println("Got it!");
                System.out.println("Now, tell me if it is a bookstore book or a library book" +
                        " (enter BB for bookstore book or LB for library book): ");

                //input either bb or lb
                bookType = input.nextLine();

                //if input is not bb or lb
                while(bookType.compareToIgnoreCase("bb") != 0 && bookType.compareToIgnoreCase("lb") != 0) {
                    System.out.println("Not a valid book type. Please enter the correct type: ");
                    bookType = input.nextLine();
                }

                System.out.println("Got it!");

                //Takes in more information for bookstore books-----------------------------------
                if(bookType.compareToIgnoreCase("bb") == 0) {
                    double percent; //pass this through
                    double price = 0; //pass this through

                    String sale, percentage;
                    String [] parsePercent; //gets rid of the percent symbol

                    System.out.println("Please enter the list price of "
                            + title.toUpperCase() + " by " + author.toUpperCase() + ": ");

                    try {
                        price = Double.parseDouble(input.nextLine());
                    }
                    catch (NumberFormatException e) {
                        System.out.println("Please enter a valid price: ");
                        price = Double.parseDouble(input.nextLine());
                    }

                    System.out.println("Is it on sale? (y/n): ");
                    sale = input.nextLine();

                    //keeps asking input if not y or n
                    while(sale.compareToIgnoreCase("y") != 0 && sale.compareToIgnoreCase("n") != 0) {
                        System.out.println("I hope you're not messing up this to test our code, try again please: ");
                        sale = input.nextLine();
                    }

                    if(sale.compareToIgnoreCase("n") == 0) percent = 0;

                    else {
                        System.out.println("Deduction percentage: ");
                        percentage = input.nextLine();

                        try {
                            parsePercent = percentage.split("%");
                            percent = Integer.parseInt(parsePercent[0]);
                        }
                        catch (NumberFormatException e) {
                            System.out.println("That is not a number, try again: ");
                            percentage = input.nextLine();
                            parsePercent = percentage.split("%");
                            percent = Integer.parseInt(parsePercent[0]);
                        }
                    }

                    System.out.println("Got it!");

                    Blist.addBook(new BookstoreBook(author, title, isbnStr, percent, sale, price));
                    System.out.println("\nHere is your bookstore book information");
                    System.out.println(Blist.getBook(isbnStr));
                }
                //--------------------------------------------------------------------------------

                //Now does the same but for library books; there are less modifiers for this type--
                else if(bookType.compareToIgnoreCase("lb") == 0) {

                    Blist.addBook(new LibraryBook(author, title, isbnStr));
                    System.out.println("\nHere is your library book information");
                    System.out.println(Blist.getBook(isbnStr));
                }
                //--------------------------------------------------------------------------------

            }

            //When the user decides to exit, the full list of books will be printed and the loop
            //will end
            else if(choice.compareToIgnoreCase("no") == 0) {
                System.out.println("Sure!");
                Blist.printList();
                break;
            }

        }

    }
}
//_________________________________
abstract class Book {
    private String author;
    private String title;
    private String isbn;

    //get and set author
    public String getAuthor() {
        return author.toUpperCase();
    }
    public void setAuthor(String author) {
        this.author = author;
    }

    //get and set title
    public String getTitle() {
        return title.toUpperCase();
    }
    public void setTitle(String title) {
        this.title = title;
    }

    //get and set isbn
    public String getIsbn() {
        return isbn;
    }
    public void setIsbn(String isbn) {
        this.isbn = isbn;
    }

    //constructors
    public Book() {
        author = "NO AUTHOR FOUND";
        title = "TITLE NOT FOUND";
        isbn = "ISBN NOT FOUND";
    }
    public Book(String isbn) {
        this.author = "NO AUTHOR FOUND";
        this.title = "TITLE NOT FOUND";
        this.isbn = isbn;
    }
    public Book(String title, String isbn) {
        this.author = "NO AUTHOR FOUND";
        this.title = title;
        this.isbn = isbn;
    }
    public Book (String author, String title, String isbn) {
        this.author = author;
        this.title = title;
        this.isbn = isbn;
    }

    //to String but is overridden
    public String toString() {
        return "[" + "-" + getIsbn() + getTitle() + " by " + getAuthor() + "]";
    }
}
//_________________________________
class BookstoreBook extends Book {
    private double discount;
    private String onSale;
    private double listPrice;

    //get and set discount
    public double getDiscount() {
        if(getOnSale().compareToIgnoreCase("n") == 0) {
            return discount;
        }

        return discount/100;
    }
    public void setDiscount(double discount) {
        this.discount = discount;
    }

    //get and set sale flag
    public String getOnSale() {
        return onSale;
    }
    public void setOnSale(String onSale) {
        this.onSale = onSale;
    }

    //get and set price
    public double getPrice() {
        return listPrice;
    }
    public void setPrice(double listPrice) {
        this.listPrice = listPrice;
    }

    //get the price after discount
    public double getPriceReduction() {
        return getPrice()-(getPrice()*getDiscount());
    }

    //constructors
    public BookstoreBook () {
        discount = 0.0;
        listPrice = 0.0;
        onSale = "SALE NOT FOUND";
    }
    public BookstoreBook (String isbn, double discount, String onSale, double listPrice) {
        super(isbn);
        setOnSale(onSale);
        setDiscount(discount);
        setPrice(listPrice);
    }
    public BookstoreBook (String title, String isbn, double discount, String onSale, double listPrice) {
        super(title, isbn);
        setOnSale(onSale);
        setDiscount(discount);
        setPrice(listPrice);
    }
    public BookstoreBook (String author, String title, String isbn, double discount, String onSale, double listPrice) {
        super(author, title, isbn);
        setOnSale(onSale);
        setDiscount(discount);
        setPrice(listPrice);
    }

    @Override
    public String toString () {
        return "[" + getIsbn() + "-" + getTitle() + " by " + getAuthor() + ", $" + String.format("%.2f", getPrice()) +
                " listed for $" + String.format("%.2f", getPriceReduction()) + "]";
    }
}
//_________________________________
class LibraryBook extends Book {
    //random number variable
    Random randInt = new Random();

    //callNum itself
    private String callNum;

    //fields for callNum constituents
    private int floorNumber;
    private String firstThreeChar;
    private char callIsbn;

    //setters for constituents
    public void setFloorNumber() {
        this.floorNumber = randInt.nextInt(1, 100); //set random number each object
    }
    public void setFirstThreeChar() {
        this.firstThreeChar = getAuthor().substring(0,3); //grabs the first three characters of String author
    }
    public void setCallIsbn() {
        this.callIsbn = getIsbn().charAt(getIsbn().length() - 1); //takes the char value at the last index of Isbn
    }

    //piece together the fields into one
    public void setCallNum() {
        if(getFloorNumber() < 10)
            this.callNum = "0%d.%s.%s".formatted(getFloorNumber(), getFirstThreeChar(), getCallIsbn());
        else
            this.callNum = "%d.%s.%s".formatted(getFloorNumber(), getFirstThreeChar(), getCallIsbn());
    }

    //getters for constituents
    public int getFloorNumber() {
        return floorNumber;
    }
    public String getFirstThreeChar() {
        return firstThreeChar;
    }
    public char getCallIsbn() {
        return callIsbn;
    }

    //getter for the callNum
    public String getCallNum() {
        return callNum;
    }

    //Constructors
    public LibraryBook(String isbnStr) {
        super(isbnStr);
        setFloorNumber();
        firstThreeChar = "null";
        setCallIsbn();
        setCallNum();
    }
    public LibraryBook(String title, String isbnStr) {
        super(title, isbnStr);
        setFloorNumber();
        firstThreeChar = "null";
        setCallIsbn();
        setCallNum();
    }
    public LibraryBook(String author, String title, String isbnStr) {
        super(author, title, isbnStr);
        setFloorNumber();
        setFirstThreeChar();
        setCallIsbn();
        setCallNum();
    }

    @Override
    public String toString() {
        return "[" + getIsbn() + "-" + getTitle() + " by " + getAuthor() + "-" + getCallNum() + "]";
    }

}
//_________________________________
class BookList {
    private Book[] list;

    //Constructor method for the list of books, setting every index to null
    public BookList() {
        list = new Book[100];
        for(int i = 0; i < 100; i++) {
            list[i] = null;
        }
    }

    //adds the book of its respective book type into the list
    public void addBook(Book b) {
        boolean full = true;
        for(int i = 0; i < 100; i++) {
            if(list[i] == null) {
                list[i] = b;
                full = false;
                break;
            }
        }
        if(full) {
            System.out.println("Sorry, no more books can be added to your list.");
        }
    }

    //returns the Book object at the index of list that matches the parameter
    public Book getBook(String isbnStr) {
        for(int i = 0; i < 100; i++) {
            if (list[i] == null) return null;
            if (isbnStr.compareToIgnoreCase(list[i].getIsbn()) == 0)
                return list[i];
        }

        return null;
    }

    //prints out the full list of books across all types
    public void printList() {
        int lb = 0, bb = 0;
        System.out.println("\nHere are all your books...");

        for(int i = 0; i < 100; i++) {
            if(list[i] instanceof LibraryBook) lb++;
            else if(list[i] instanceof BookstoreBook) bb++;
        }

        System.out.println("Library Books (" + lb + ")");

        for(Book b: list) {
            if(b instanceof LibraryBook)
                System.out.println("\t\t" + b.toString());
        }

        System.out.println("\n----");

        System.out.println("Bookstore Books (" + bb + ")");
        for(Book b: list) {
            if(b instanceof BookstoreBook)
                System.out.println("\t\t" + b.toString());
        }

        System.out.println("\n----");
        System.out.println("Take care now!");
    }
}
