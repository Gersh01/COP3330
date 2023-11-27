//Final Project
//Alexander Gershfeld and Gabriel Perez
//Hatim Boustique
//COP3330
//December 1, 2023

import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;

public class FinalProject {
    public static void main(String[] args) throws FileNotFoundException {
        int option;
        String tmpId = null;
        Scanner input = new Scanner(System.in);

        //set the Array list to act as our data structure
        ArrayList<Person> pList = new ArrayList<Person>();

        //exception handling switch statement
        boolean sentinel = true;
        while (sentinel) {
            //print menu, make main less cluttered with sysouts
            printMenu();

            //catch the input for the menu selection, handle any exception with input
            try {
                option = input.nextInt();
                input.nextLine();

            } catch (Exception e) {
                System.out.println("You entered an invalid input - try again");
                input.nextLine();
                continue;
            }

            //switch to sort selection input to its functionality
            switch (option) {
                case 1:
                    System.out.println("\nEnter the faculty info:");
                    System.out.println("---------------------------------------------------------------------------");
                    pList.add ( new Faculty
                        (
                            inputName(input),
                            inputID(input, pList),
                            inputDepartment(input),
                            inputRank(input)
         
                            
                        )
                    );
                    System.out.println("\nFaculty member added!");
                    break;
                case 2:
                    System.out.println("\nEnter the student info:");
                    System.out.println("---------------------------------------------------------------------------");
                    pList.add ( new Student
                        (
                            inputName(input),
                            inputID(input, pList),
                            inputGPA(input),
                            inputCrdHrs(input)
                        )
                    );
                    
                    System.out.println("\nStudent member added!");
                    break;
                case 3:
                    System.out.print("Enter the Student's id: ");
                    if(!printObject(input, pList))
                        System.out.println("\nNo Student matched!");
                    break;
                case 4:
                    System.out.print("Enter the Faculty's id: ");
                    if(!printObject(input, pList))
                        System.out.println("\nNo Faculty member matched!");
                    break;
                case 5:
                    System.out.println("\nEnter the staff info: ");
                    System.out.println("---------------------------------------------------------------------------");
                    pList.add ( new Staff
                        (
                            inputName(input),
                            inputID(input, pList),
                            inputDepartment(input),
                            inputStatus(input)
                        )
                    );
                    System.out.println("\nStaff member added!");
                    break;
                case 6:
                    System.out.print("Enter the Staff's id: ");
                    if(!printObject(input, pList))
                        System.out.println("\nNo Staff member matched!");
                    break;
                case 7:
                    boolean exist = false;
                    System.out.print("Enter the id of the person to delete: ");
                    tmpId = input.nextLine();
                    for(Person p: pList) {
                        if(p.getId().compareToIgnoreCase(tmpId) == 0) {
                            System.out.println("\n" + p.getName() + " successfully deleted");
                            pList.remove(p);
                            exist = true;
                            break;
                        }
                    }
                    if(!exist)
                        System.out.println("\nSorry no such person exists");
                    break;
                case 8:
                    sentinel = false;
                    exitProtocol(input, pList);
                    break;
                default:
                    System.out.println("You entered an invalid input - try again");
                    break;
            }
        }
    }
    //method to be called every cycle of instruction
    public static void printMenu() {
        System.out.println("---------------------------------------------------------------------------");
        System.out.println("Choose one of the options:");
        System.out.println("1 - Enter the information of a faculty");
        System.out.println("2 - Enter the information of a student");
        System.out.println("3 - Print tuition invoice for a student");
        System.out.println("4 - Print faculty information");
        System.out.println("5 - Enter the information of a staff member");
        System.out.println("6 - Print the information of a staff member");
        System.out.println("7 - Delete a person");
        System.out.println("8 - Exit Program");
        System.out.println("---------------------------------------------------------------------------");
        System.out.print("Enter your selection: ");
    }

    //checks if the ID is in correct format
    public static boolean checkID(String id) {
        int len = id.length();
        if (len != 6) return false;
        for (int i = 0; i < len; i++) {
            if (i < 2)
                if (!Character.isAlphabetic(id.charAt(i)))
                    return false;
            if (i >= 2)
                if (!Character.isDigit(id.charAt(i)))
                    return false;
        }

        return true;
    }

    //Input methods with exception handling - declutter the switch in main method
    public static String inputName(Scanner input) {
        String fullName = null;
        while (true) {
            try {
                System.out.print("Name of the person: ");
                fullName = input.nextLine();

                for (int i = 0; i < fullName.length(); i++)
                    if (Character.isDigit(fullName.charAt(i)))
                        throw new Exception();
                break;
            } catch (Exception e) {
                System.out.println(fullName + " is an invalid input - try again");
                continue;
            }
        }
        return fullName;
    }
    public static String inputID(Scanner input, ArrayList<Person> list) {
        String id = null;
        while (true) {
            try {
                System.out.print("ID: ");
                id = input.nextLine();
                if (!checkID(id)) throw new Exception();
                for (Person p : list)
                    if (p != null && id.compareToIgnoreCase(p.getId()) == 0)
                        throw new RuntimeException();

                break;
            } catch (RuntimeException e) {
                System.out.println(id + " is already assigned - try again");
                continue;
            } catch (Exception e) {
                System.out.println("Invalid ID format. Must be LetterLetterDigitDigitDigitDigit");
                continue;
            }
        }

        return id;
    }
    public static String inputDepartment(Scanner input) {
        String department = null;
        while (true) {
            try {
                System.out.print("Department: ");
                department = input.nextLine();
                if
                (
                        department.compareToIgnoreCase("mathematics") == 0 ||
                                department.compareToIgnoreCase("engineering") == 0 ||
                                department.compareToIgnoreCase("english") == 0
                )
                    break;
                else throw new Exception();
            } catch (Exception e) {
                System.out.println(department + " is an invalid input - try again");
                continue;
            }
        }

        return department;
    }
    public static String inputRank(Scanner input) {
        String rank = null;
        while (true) {
            try {
                System.out.print("Rank: ");
                rank = input.nextLine();
                if
                (
                    rank.compareToIgnoreCase("professor") == 0 ||
                    rank.compareToIgnoreCase("adjunct") == 0
                )
                    break;
                else throw new Exception();
            } catch (Exception e) {
                System.out.println('"' + rank + '"' + " is invalid");
                continue;
            }
        }
        return rank;
    }
    public static String inputStatus(Scanner input) {
        String status = null;
        while(true) {
            try {
                System.out.print("Status - Enter P for part time, F for full time: ");
                status = input.nextLine();
                if
                (
                    status.compareToIgnoreCase("p") == 0 ||
                    status.compareToIgnoreCase("f") == 0
                )
                    break;
                else throw new Exception();
            } catch (Exception e) {
                System.out.println(status + " is an invalid input - try again");
                continue;
            }
        }
        return status;
    }
    public static double inputGPA(Scanner input) {
        double gpa = 0;
        while(true) {
            try {
                System.out.print("Enter GPA between 0.00 - 4.00: ");
                gpa = input.nextDouble();
                if(gpa < 0 || gpa > 4.00)
                    throw new Exception();
                else
                	break;
            } catch(Exception e) {
                System.out.println(gpa + " is an invalid input - try again");
                continue;
            }
            finally {
            	input.nextLine();
            }
        }
        return gpa;
    }
    public static int inputCrdHrs(Scanner input) {
        int creditHours = 0;
        while(true) {
            try {
                System.out.print("Enter credit hours taken - must be greater than 0: ");
                creditHours = input.nextInt();

                if(creditHours < 0) throw new Exception();
                else break;
            } catch(Exception e) {
                System.out.println(creditHours + " is an invalid input - try again");
                continue;
            }
            finally {
            	input.nextLine();
            }
        }
        return creditHours;
    }

    //matching ids and printing the object
    public static boolean printObject(Scanner input, ArrayList<Person> list) {
        String tmpId = null;
        tmpId = input.nextLine();
        for(Person p: list) {
            if (p.getId().compareToIgnoreCase(tmpId) == 0) {
                ((Personable) p).print();
                return true;
            }
        }
        return false;
    }

    //saves a file with sorted list based on user input -- exits sequence
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
                System.out.println(reportOption + " is an invalid input - try again");
                continue;
            }
        }
        if(reportOption.compareToIgnoreCase("y") == 0) {
            while (true) {
                try {
                    System.out.print("Would like to sort your students by descending gpa or name (1 for gpa, 2 for name): ");
                    sortOption = input.nextInt();
                    
                    if (sortOption == 1 || sortOption == 2)
                        break;
                    else throw new Exception();
                } catch (Exception e) {
                    System.out.println(sortOption + " is an invalid input - try again");
                    continue;
                }
                finally {
                	input.nextLine();
                }
            }

            reportWriter(sortOption, list);
            System.out.println("Report created and saved on your hard drive!");
        }
        System.out.println("Goodbye!");
    }
    public static void reportWriter(int option, ArrayList<Person> list) throws FileNotFoundException {
        PrintWriter file = new PrintWriter("report.txt");
        int listedObject = 1;

        file.println("Report created on " + java.time.LocalDate.now());
        file.println("****************************************");
        file.println("\nFaculty Members");
        file.println("----------------------------------------");

        //Printing the faculty
        for (Person value : list) {
            if (value instanceof Faculty) {
                file.println("\t" + listedObject++ + ". " + value.getName());
                file.println("\tID: " + value.getId());
                file.println("\t" + ((Faculty) value).getRank() + ", " + ((Faculty) value).getDepartment() + "\n");
            }
        }

        file.println("\nStaff Members");
        file.println("----------------------------------------");

        //Printing the staff
        listedObject = 1;
        for (Person person : list) {
            if (person instanceof Staff) {
                file.println("\t" + listedObject++ + ". " + person.getName());
                file.println("\tID: " + person.getId());
                file.println("\t" + ((Staff) person).getDepartment() + ", " + ((Staff) person).getStatus() + "\n");
            }
        }

        //Printing the students
        ArrayList<Student> sortList = new ArrayList<Student>();
        listedObject = 1;
        for(Person p: list)
            if(p instanceof Student)
                sortList.add((Student)p);
        if(option == 1) {
            file.println("\nStudents Members (sorted by descending GPA)");
            file.println("----------------------------------------");

            sortList.sort(Comparator.comparingDouble(Student::getGpa));
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

            sortList.sort(Comparator.comparing(Student::getName).reversed());
            for (Student s: sortList) {
                file.println("\t" + listedObject++ + ". " + s.getName());
                file.println("\tID: " + s.getId());
                file.println("\tGpa: " + s.getGpa());
                file.println("\tCredit hours: " + s.getCreditHours() + "\n");
            }
        }

        file.flush();
        file.close();
    }
}



//---------------------------------
interface Personable {
    void print();
}

//---------------------------------
abstract class Person implements Personable {
    private String name;
    private String id;

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

    public Person() {
        name = "Person not found";
        id = "id not available";
    }

    public Person(String name, String id) {
        this.name = name;
        this.id = id;
    }

    public abstract void print();
}

//---------------------------------
class Student extends Person {
    private double gpa;
    private int creditHours;

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

    @Override
    public void print() {
        double total = (getCreditHours() * 236.45) + 52;
        double discount = (getCreditHours() * 236.45 * .25);
        double totalDiscount = total - discount;
        
        System.out.println("---------------------------------------------------------------------------");
        System.out.println(getName() + "\t" + getId());
        System.out.println("Credit hours: " + getCreditHours() + " ($236.45/credit hour)");
        System.out.println("Fees: $52");
        if(getGpa() >= 3.85) {
            System.out.println("Total payment (after discount): $" + String.format("%.2f", totalDiscount) + "\t" + "(" + String.format("%.2f", discount) + "$ discount applied)");
        }
        else {
            System.out.println("Total payment (after discount): $" + String.format("%.2f", total) + "\t" + "(0$ discount applied)");
        }
    }
}

//---------------------------------
abstract class Employee extends Person implements Personable {
    private String department;

    public String getDepartment() {
        String dep = department;

        if(department.compareToIgnoreCase("mathematics") == 0) dep = "Mathematics";
        else if(department.compareToIgnoreCase("english") == 0) dep = "English";
        else dep = "Engineering";

        return dep;
    }

    public void setDepartment(String department) {
        this.department = department;
    }

    public Employee() {
        super();
        this.department = "Department not found";
    }

    public Employee(String name, String id, String department) {
        super(name, id);
        setDepartment(department);
    }

    public abstract void print();
}

//---------------------------------
class Faculty extends Employee {
    private String rank;

    public String getRank() {
        String tmpRank = rank;

        if(rank.compareToIgnoreCase("professor") == 0) tmpRank = "Professor";
        else tmpRank = "Adjunct";

        return tmpRank;
    }

    public void setRank(String rank) {
        this.rank = rank;
    }

    public Faculty() {
        super();
        rank = "Rank not found";
    }

    public Faculty(String name, String id, String department, String rank) {
        super(name, id, department);
        setRank(rank);
    }

    @Override
    public void print() {
        System.out.println("---------------------------------------------------------------------------");
        System.out.println(getName() + "\t\t" + getId());
        System.out.println(getDepartment() + " Department, " + getRank());
    }
}

//---------------------------------
class Staff extends Employee {
    private String status;

    public String getStatus() {
        String tmpStatus = status;

        if(tmpStatus.compareToIgnoreCase("p") == 0) tmpStatus = "Part Time";
        else tmpStatus = "Full Time";

        return tmpStatus;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public Staff() {
        super();
        status = "Rank not found";
    }

    public Staff(String name, String id, String department, String status) {
        super(name, id, department);
        setStatus(status);
    }

    @Override
    public void print() {
        System.out.println("---------------------------------------------------------------------------");
        System.out.println(getName() + "\t\t" + getId());
        System.out.println(getDepartment() + " Department, " + getStatus());

    }
}
