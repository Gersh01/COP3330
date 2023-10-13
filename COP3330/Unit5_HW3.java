//Unit5_HW3
//Alexander Gershfeld, Tyler Huynh, Gabriel Perez
//Hatim Boustique
//COP3330
//October 15, 2023

import java.util.Scanner;

public class Driver {
    public static void main(String[] args) {
        BookList Blist = new BookList(); //creates the list for the books to be held

        Scanner input = new Scanner(System.in);

        String bookEntry, bookType, author, title, isbnStr; //information that all books have

        String [] bookInfo;
        int isbn; //pass this number instead of the string version

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
                try {
                    bookEntry = input.nextLine();
                    bookInfo = bookEntry.split("/");
                    author = bookInfo[0];
                    title = bookInfo[1];
                    isbnStr = bookInfo[2];
                }
                catch(ArrayIndexOutOfBoundsException e) {
                    System.out.println("You did not provide a valid selection, make sure there's an author/title/isbn" +
                            ". Please try again: ");

                    bookEntry = input.nextLine();
                    bookInfo = bookEntry.split("/");
                    author = bookInfo[0];
                    title = bookInfo[1];
                    isbnStr = bookInfo[2];
                }

                try {
                    isbn = Integer.parseInt(isbnStr);
                }
                catch(NumberFormatException e) {
                    System.out.println("ISBN is not a valid number, please insert the correct ISBN only: ");

                    isbnStr = input.nextLine();
                    isbn = Integer.parseInt(isbnStr);
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
                    int percent; //pass this through
                    double price; //pass this through

                    String sale, percentage;
                    String [] parsePercent; //gets rid of the percent symbol

                    System.out.println("Please enter the list price of "
                            + title.toUpperCase() + " by " + author.toUpperCase() + ": ");

                    try {
                        price = Double.parseDouble(input.nextLine());
                    }
                    catch(NumberFormatException e) {
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

                    System.out.println("Deduction percentage: ");
                    percentage = input.nextLine();

                    try {
                        parsePercent = percentage.split("%");
                        percent = Integer.parseInt(parsePercent[0]);
                    }
                    catch(NumberFormatException e) {
                        System.out.println("That is not a number, try again: ");
                        percentage = input.nextLine();
                        parsePercent = percentage.split("%");
                        percent = Integer.parseInt(parsePercent[0]);
                    }

                    System.out.println("Got it!");

                    //pass all of the book information through the book class, then into BookstoreBook
                    Blist.addBook(new //Constructor goes here);
                    System.out.println("\n\nHere is your bookstore book information");
                    //method that calls the toString of the book
                }
                //--------------------------------------------------------------------------------

                //Now does the same but for library books; there are less modifiers for this type--
                else if(bookType.compareToIgnoreCase("lb") == 0) {

                    //pass all of the book information through the book class, then into LibraryBook
                    Blist.addBook(new //Constructor goes here);
                    System.out.println("\n\nHere is your library book information");
                    //method that calls the toString of the book
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
    //code of the abstract class Book
    //You may add an abstract method if you see fit...
}
//_________________________________
class BookstoreBook extends Book {
    //fields and specific code to the BookstoreBook class goes here
}
//_________________________________
class LibraryBook extends Book {
    //fields and specific code to the LibraryBook class goes here
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
        if(full) System.out.println("Sorry, no more books can be added to your list.");
    }

    //prints out the full list of books across all types
    public void printList() {
        int lb = 0, bb = 0;
        System.out.println("Here are all your books...");

        for(int i = 0; i < 100; i++) {
            if(list[i] instanceof LibraryBook) lb++;
            else if(list[i] instanceof BookstoreBook) bb++;
        }

        System.out.println("Library Books (" + lb + ")");

        for(Book b: list) {
            if(b instanceof LibraryBook)
                System.out.println("\t\t" + b.toString());
        }

        System.out.println("\n\n----");

        System.out.println("Bookstore Books (" + bb + ")");
        for(Book b: list) {
            if(b instanceof BookstoreBook)
                System.out.println("\t\t" + b.toString());
        }

        System.out.println("\n\n----");
        System.out.println("Take care now!");
    }
}
