//Final Project
//Alexander Gershfeld and Gabriel Perez
//Hatim Boustique
//COP3330
//December 1, 2023

import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Scanner;

public class FinalProject {
    public static void main(String[] args) throws FileNotFoundException {
    	System.out.println("\n\t\t\t\t\t\t\tWelcome to my Personal Management Program\n");
        int option;
        String tmpId = null;
        Scanner input = new Scanner(System.in);

        //set the Array list to act as our data structure
        ArrayList<Person> pList = new ArrayList<Person>();

        //start of the menu program, continues until user selects 8 - exit
        boolean sentinel = true;
        while (sentinel) {
            //print menu, make main less cluttered with sysouts
            printMenu();

            //catch the input for the menu selection, handle any exception with input
            try {
                option = input.nextInt();
                input.nextLine();

            } catch (Exception e) {
                System.out.println("\n\nInvalid entry - try again\n\n");
                input.nextLine();
                continue;
            }

            //switch to sort selection input to its functionality
            switch (option) {
                case 1: //Add faculty
                    System.out.println("\nEnter the faculty info:");
                    pList.add ( new Faculty //runs through each method collecting input then adds to list
                        (
                            inputName(input,1),
                            inputID(input, pList),
                            inputRank(input),
                            inputDepartment(input)
                        )
                    );
                    System.out.println("\nFaculty added!\n");
                    break;
                case 2: //Add student
                    System.out.println("\nEnter the student info:");
                    
                    pList.add ( new Student
                        (
                            inputName(input,2),
                            inputID(input, pList),
                            inputGPA(input),
                            inputCrdHrs(input)
                        )
                    );
                    System.out.println("\nStudent added!\n");
                    break;
                case 3: //Print invoice
                    System.out.print("\n\tEnter the Student's id: ");
                    if(!printObject(input, pList)) //if function fails - student not found
                        System.out.println("\n\tNo Student matched!\n\n");
                    break;
                case 4: //Print faculty
                    System.out.print("\n\tEnter the Faculty's id: ");
                    if(!printObject(input, pList))
                        System.out.println("\n\tNo Faculty member matched!\n\n");
                    break;
                case 5: //Add staff
                    System.out.println("\nEnter the staff info: ");
                    pList.add ( new Staff
                        (
                            inputName(input, 5),
                            inputID(input, pList),
                            inputDepartment(input),
                            inputStatus(input)
                        )
                    );
                    System.out.println("\nStaff member added!\n");
                    break;
                case 6: //Print staff
                    System.out.print("\n\tEnter the Staff's id: ");
                    if(!printObject(input, pList))
                        System.out.println("\n\tNo Staff member matched!\n\n");
                    break;
                case 7: //Delete person
                    boolean exist = false;
                    System.out.print("\n\tEnter the id of the person to delete: ");
                    tmpId = input.nextLine(); //grab the ID to match
                    for(Person p: pList) { //find the person with matching ID
                        if(p.getId().compareToIgnoreCase(tmpId) == 0) {
                            System.out.println("\n" + p.getName() + " successfully deleted");
                            pList.remove(p); //removes from list
                            exist = true;
                            break;
                        }
                    }
                    if(!exist) //not exists = no person
                        System.out.println("\n\tSorry no such person exists.\n\n");
                    break;
                case 8:
                    sentinel = false; //break the loop after switch
                    exitProtocol(input, pList); //series of routines to properly exit program
                    break;
                default:
                    System.out.println("\nInvalid entry - try again\n");
                    break;
            }
        }
    }

    //method to be called every cycle of instruction
    public static void printMenu() {
        System.out.println("Choose one of the options:");
        System.out.println("1 - Enter the information of a faculty");
        System.out.println("2 - Enter the information of a student");
        System.out.println("3 - Print tuition invoice for a student");
        System.out.println("4 - Print faculty information");
        System.out.println("5 - Enter the information of a staff member");
        System.out.println("6 - Print the information of a staff member");
        System.out.println("7 - Delete a person");
        System.out.println("8 - Exit Program");
        System.out.print("\n\tEnter your selection: ");
    }

    //checks if the ID is in correct format
    public static boolean checkID(String id) {
        int len = id.length();
        if (len != 6) return false; //input too large
        for (int i = 0; i < len; i++) {
            if (i < 2)
                if (!Character.isAlphabetic(id.charAt(i))) //one of the first two characters is a digit
                    return false;
            if (i >= 2)
                if (!Character.isDigit(id.charAt(i))) //the last four digits is a character
                    return false;
        }

        return true;
    }

    //Input methods with exception handling - declutter the switch in main method
    public static String inputName(Scanner input, int val) {
        String fullName = null;
        while (true) {
            try {
            	if(val == 1) {
            		System.out.print("\tName of the faculty: ");
            	}
            	
            	else if(val == 2) {
            		System.out.print("\tName of Student: ");
            	}
            	
            	else if(val == 5) {
            		System.out.print("\tName of the staff member: ");
            	}
            		
                fullName = input.nextLine();

                for (int i = 0; i < fullName.length(); i++)
                    if (Character.isDigit(fullName.charAt(i))) //digits don't belong in names
                        throw new Exception();
                break;
            } catch (Exception e) {
                System.out.println("\n\tInvalid entry - try again\n");
                continue;
            }
        }
        return fullName;
    }
    public static String inputID(Scanner input, ArrayList<Person> list) {
        String id = null;
        while (true) {
            try {
                System.out.print("\tID: ");
                id = input.nextLine();

                //using helper function to check formatting of ID
                if (!checkID(id)) throw new Exception();
                for (Person p : list)
                    if (p != null && id.compareToIgnoreCase(p.getId()) == 0) //checks for matching IDs
                        throw new RuntimeException(); //different exception for different type of invalid input

                break;
            } catch (RuntimeException e) {
                System.out.println(id + " is already assigned - try again");
                continue;
            } catch (Exception e) {
                System.out.println("\n\tInvalid ID format. Must be LetterLetterDigitDigitDigitDigit\n");
                continue;
            }
        }

        return id;
    }
    public static String inputDepartment(Scanner input) {
        String department = null;
        while (true) {
            try {
                System.out.print("\tDepartment: ");
                department = input.nextLine();
                if //must be one of the three departments
                (
                    department.compareToIgnoreCase("mathematics") == 0 ||
                    department.compareToIgnoreCase("engineering") == 0 ||
                    department.compareToIgnoreCase("english") == 0
                )
                    break;
                else throw new Exception();
            } catch (Exception e) {
                System.out.println("\n\t" + '"' + department + '"' + " is invalid\n");
                continue;
            }
        }

        return department;
    }
    public static String inputRank(Scanner input) {
        String rank = null;
        while (true) {
            try {
                System.out.print("\tRank: ");
                rank = input.nextLine();
                if //must be one of the two ranks
                (
                    rank.compareToIgnoreCase("professor") == 0 ||
                    rank.compareToIgnoreCase("adjunct") == 0
                )
                    break;
                else throw new Exception();
            } catch (Exception e) {
                System.out.println("\n\t" + '"' + rank + '"' + " is invalid\n");
                continue;
            }
        }
        return rank;
    }
    public static String inputStatus(Scanner input) {
        String status = null;
        while(true) {
            try {
                System.out.print("\tStatus - Enter P for part time, F for full time: ");
                status = input.nextLine();
                if //must be either p or f
                (
                    status.compareToIgnoreCase("p") == 0 ||
                    status.compareToIgnoreCase("f") == 0
                )
                    break;
                else throw new Exception();
            } catch (Exception e) {
                System.out.println("\n\t" + '"' + status + '"' + " is invalid\n");
                continue;
            }
        }
        return status;
    }
    public static double inputGPA(Scanner input) {
        double gpa = 0;
        while(true) {
            try {
                System.out.print("\tGPA: ");
                gpa = input.nextDouble();
                if(gpa < 0 || gpa > 4.00) //must be within gpa range
                    throw new Exception();
                else
                    break;
            } catch(Exception e) {
                System.out.println("\n\tInvalid entry - try again\n");
                continue;
            }
            finally {
                input.nextLine(); //clear the input stream
            }
        }
        return gpa;
    }
    public static int inputCrdHrs(Scanner input) {
        int creditHours = 0;
        while(true) {
            try {
                System.out.print("\tCredit Hours: ");
                creditHours = input.nextInt();

                if(creditHours < 0) throw new Exception(); //input cant be a negative number
                else break;
            } catch(Exception e) {
                System.out.println("\n\tInvalid entry - try again\n");
                continue;
            }
            finally {
                input.nextLine(); //clear input stream
            }
        }
        return creditHours;
    }

    //matching ids and printing the object
    public static boolean printObject(Scanner input, ArrayList<Person> list) {
        String tmpId = null;
        tmpId = input.nextLine();
        for(Person p: list) { //match the ID to the person inside the list
            if (p.getId().compareToIgnoreCase(tmpId) == 0) {
                ((Personable) p).print(); //cast as interface and print
                return true;
            }
        }
        return false; //ID not found in list
    }

    //saves a file with sorted list based on user input -- exit sequence
    public static void exitProtocol(Scanner input, ArrayList<Person> list) throws FileNotFoundException {
        String reportOption = null;
        int sortOption = 0;

        while(true) {
            try {
                System.out.print("Would you like to create the report? (Y/N): ");
                reportOption = input.nextLine();

                if(reportOption.compareToIgnoreCase("y") == 0 || reportOption.compareToIgnoreCase("n") == 0)
                    break;
                else throw new Exception();
            } catch(Exception e) {
                System.out.println("\nInvalid entry - try again\n");
                continue;
            }
        }

        if(reportOption.compareToIgnoreCase("y") == 0) { //if the user wants to print a report
            while (true) {
                try {
                    System.out.print("Would like to sort your students by descending gpa or name (1 for gpa, 2 for name): ");
                    sortOption = input.nextInt();

                    if (sortOption == 1 || sortOption == 2)
                        break;
                    else throw new Exception();
                } catch (Exception e) {
                    System.out.println("\nInvalid entry - try again\n");
                    continue;
                }
                finally {
                    input.nextLine();
                }
            }

            reportWriter(sortOption, list); //write the report and take in the type of sort value
            System.out.println("Report created and saved on your hard drive!");
        }
        System.out.println("Goodbye!");
    }
    public static void reportWriter(int option, ArrayList<Person> list) throws FileNotFoundException {
        PrintWriter file = new PrintWriter("report.txt"); //create a new file stream
        int listedObject = 1; //formatting only

        file.println("Report created on " + java.time.LocalDate.now()); //grab the date of runtime
        file.println("****************************************");
        file.println("\nFaculty Members");
        file.println("----------------------------------------");

        //Printing the faculty
        for (Person value : list) {
            if (value instanceof Faculty) { //print to file for every instance of faculty
                file.println("\t" + listedObject++ + ". " + value.getName());
                file.println("\tID: " + value.getId());
                file.println("\t" + ((Faculty) value).getRank() + ", " + ((Faculty) value).getDepartment() + "\n");
            }
        }

        file.println("\nStaff Members");
        file.println("----------------------------------------");

        //Printing the staff
        listedObject = 1; //reset the formatting number
        for (Person person : list) {
            if (person instanceof Staff) { //print to screen for every instance of staff
                file.println("\t" + listedObject++ + ". " + person.getName());
                file.println("\tID: " + person.getId());
                file.println("\t" + ((Staff) person).getDepartment() + ", " + ((Staff) person).getStatus() + "\n");
            }
        }

        //Printing the students
        ArrayList<Student> sortList = new ArrayList<Student>(); //helper list
        listedObject = 1; //reset the formatting number
        for(Person p: list)
            if(p instanceof Student) //for every instance of student add to helper list
                sortList.add((Student)p);
        if(option == 1) { //sorting by GPA
            file.println("\nStudents Members (sorted by descending GPA)");
            file.println("----------------------------------------");

            //sort the helper list by comparing the gpa, then reverse it for descending order
            sortList.sort(Comparator.comparingDouble(Student::getGpa).reversed());
            for (Student s: sortList) {
                file.println("\t" + listedObject++ + ". " + s.getName());
                file.println("\tID: " + s.getId());
                file.println("\tGpa: " + s.getGpa());
                file.println("\tCredit hours: " + s.getCreditHours() + "\n");
            }
        }
        else {
            file.println("\nStudents Members (sorted by descending name)");
            file.println("----------------------------------------");

            //sort the helper list by comparing the names, comparator is already in descending order
            sortList.sort(Comparator.comparing(Student::getName));
            for (Student s: sortList) {
                file.println("\t" + listedObject++ + ". " + s.getName());
                file.println("\tID: " + s.getId());
                file.println("\tGpa: " + s.getGpa());
                file.println("\tCredit hours: " + s.getCreditHours() + "\n");
            }
        }

        //make sure to flush before you close the lid
        file.flush();
        file.close();
    }
}

//---------------------------------
interface Personable {
    void print(); //le print
}

//---------------------------------
abstract class Person implements Personable {
    private String name;
    private String id;

    //setter and getters
    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }
    public String getId() {
        return id;
    }
    public void setId(String id) {
        this.id = id;
    }

    //constructors
    public Person() {
        name = "Person not found";
        id = "id not available";
    }
    public Person(String name, String id) {
        this.name = name;
        this.id = id;
    }

    //le print
    public abstract void print();
}

//---------------------------------
class Student extends Person {
    private double gpa;
    private int creditHours;

    //setter and getters
    public double getGpa() {
        return gpa;
    }
    public void setGpa(double gpa) {
        this.gpa = gpa;
    }
    public int getCreditHours() {
        return creditHours;
    }
    public void setCreditHours(int creditHours) {
        this.creditHours = creditHours;
    }

    //constructors
    public Student() {
        super();
        gpa = 0.00;
        creditHours = 0;
    }
    public Student (String name, String id, double gpa, int creditHours) {
        super(name, id);
        setGpa(gpa);
        setCreditHours(creditHours);
    }

    //print version student
    @Override
    public void print() {
        //make the math into variables for clarity
        double total = (getCreditHours() * 236.45) + 52;
        double discount = (getCreditHours() * 236.45 * .25);
        double totalDiscount = total - discount;
        
        System.out.println("\n\nHere is the tuition invoice for " + getName() + ":\n\n");
        System.out.println("---------------------------------------------------------------------------");
        System.out.println(getName() + "\t" + getId());
        System.out.println("Credit hours: " + getCreditHours() + " ($236.45/credit hour)");
        System.out.println("Fees: $52");

        //determine if discount is applicable
        if(getGpa() >= 3.85) {
            System.out.println("Total payment (after discount): $" + String.format("%.2f", totalDiscount) + "\t" + "(" + String.format("%.2f", discount) + "$ discount applied)");
        }
        else {
            System.out.println("Total payment (after discount): $" + String.format("%.2f", total) + "\t" + "(0$ discount applied)");
        }
        System.out.println("---------------------------------------------------------------------------\n\n");
    }
}

//---------------------------------
abstract class Employee extends Person implements Personable {
    private String department;

    //setters and getters
    public String getDepartment() {
        String dep = department;

        //format the department field correctly
        if(department.compareToIgnoreCase("mathematics") == 0) dep = "Mathematics";
        else if(department.compareToIgnoreCase("english") == 0) dep = "English";
        else dep = "Engineering";

        return dep;
    }
    public void setDepartment(String department) {
        this.department = department;
    }

    //constructors
    public Employee() {
        super();
        this.department = "Department not found";
    }
    public Employee(String name, String id, String department) {
        super(name, id);
        setDepartment(department);
    }

    //le print
    public abstract void print();
}

//---------------------------------
class Faculty extends Employee {
    private String rank;

    //setters and getters
    public String getRank() {
        String tmpRank = rank;

        //format the rank field correctly
        if(rank.compareToIgnoreCase("professor") == 0) tmpRank = "Professor";
        else tmpRank = "Adjunct";

        return tmpRank;
    }
    public void setRank(String rank) {
        this.rank = rank;
    }

    //constructors
    public Faculty() {
        super();
        rank = "Rank not found";
    }
    public Faculty(String name, String id, String rank, String department) {
        super(name, id, department);
        setRank(rank);
    }

    //print version faculty
    @Override
    public void print() {
        System.out.println("\n\n---------------------------------------------------------------------------");
        System.out.println(getName() + "\t\t" + getId());
        System.out.println(getDepartment() + " Department, " + getRank());
        System.out.println("---------------------------------------------------------------------------\n\n");
    }
}

//---------------------------------
class Staff extends Employee {
    private String status;

    //setters and getters
    public String getStatus() {
        String tmpStatus = status;

        //format status field correctly
        if(tmpStatus.compareToIgnoreCase("p") == 0) tmpStatus = "Part Time";
        else tmpStatus = "Full Time";

        return tmpStatus;
    }
    public void setStatus(String status) {
        this.status = status;
    }

    //constructors
    public Staff() {
        super();
        status = "Rank not found";
    }
    public Staff(String name, String id, String department, String status) {
        super(name, id, department);
        setStatus(status);
    }

    //print version staff
    @Override
    public void print() {
        System.out.println("\n\n---------------------------------------------------------------------------");
        System.out.println(getName() + "\t\t" + getId());
        System.out.println(getDepartment() + " Department, " + getStatus());
        System.out.println("---------------------------------------------------------------------------\n\n");

    }
}
