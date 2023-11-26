//Final Project
//Alexander Gershfeld and Gabriel Perez
//Hatim Boustique
//COP3330
//December 1, 2023

import java.util.Scanner;

public class FinalProject {
    public static void main(String[] args) {
        int option;
        Scanner input = new Scanner(System.in);

        //set the Array list to act as our data structure
        Person[] pList = new Person[100];
        for (int i = 0; i < 100; i++)
            pList[i] = null;

        //print menu, make main less cluttered with sysouts
        printMenu();

        //catch the input for the menu selection, handle any exception with input
        while (true) {
            try {
                option = input.nextInt();
                input.nextLine();
                break;
            } catch (Exception e) {
                System.out.println("You entered an invalid input - try again");
                continue;
            }
        }


        //exception handling switch statement
        boolean sentinel = true;
        String fullName = null, id = null, department = null, rank = null, status = null;
        double gpa;
        int creditHours;
        while (sentinel) {

            sentinel = false;
            switch (option) {
                case 1:
                    System.out.println("Enter the faculty info:\n");
                    while (true) {
                        try {
                            System.out.print("Name of the faculty: ");
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
                    while (true) {
                        try {
                            System.out.print("ID: ");
                            id = input.nextLine();
                            if (!checkID(id)) throw new Exception();
                            for (Person p : pList)
                                if (p != null && id.compareToIgnoreCase(p.getId()) == 0)
                                    throw new RuntimeException();

                            break;
                        } catch (RuntimeException e) {
                            System.out.println(id + " is already assigned - try again");
                            continue;
                        } catch (Exception e) {
                            System.out.println(id + " is an invalid input - try again");
                            continue;
                        }
                    }
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
                            System.out.println(rank + " is an invalid input - try again");
                            continue;
                        }
                    }
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

                    for(int i = 0; i < 100; i++) {
                        if(pList[i] != null) {
                            pList[i] = new Faculty(fullName, id, rank, department);
                            pList[i].print();
                        }
                    }

                    break;
                case 2:
                    System.out.println("2 - Enter the information of a student");
                    break;
                case 3:
                    System.out.println("3 - Print tuition invoice for a student");
                    break;
                case 4:
                    System.out.println("4 - Print faculty information");
                    break;
                case 5:
                    System.out.println("5 - Enter the information of a staff member");
                    break;
                case 6:
                    System.out.println("6 - Print the information of a staff member");
                    break;
                case 7:
                    System.out.println("7 - Delete a person");
                    break;
                case 8:
                    System.out.println("8 - Exit Program");
                    break;
                default:
                    System.out.println("You entered an invalid input - try again");
                    sentinel = true;
                    break;
            }
        }
    }
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
        System.out.print("Enter your selection: ");
    }
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
}

interface Personable {
/*
    void printTuition();
    void printFaculty();
    void printStaff();
 */
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
        setName("Person Not found");
        setId("Id not found");
        gpa = 0.00;
        creditHours = 0;
    }

    public Student (String name, String id, double gpa, int creditHours) {
        setName(name);
        setId(id);
        setGpa(gpa);
        setCreditHours(creditHours);
    }

    @Override
    public void print() {
        System.out.println("---------------------------------------------------------------------------");
        System.out.println(getName() + "\t" + getId());
        System.out.println("Credit hours:" + getCreditHours() + " ($236.45/credit hour)");
        System.out.println("Fees: $52");
        if(getGpa() >= 3.85) {
            System.out.println("Total payment (after discount): $" + ((getCreditHours() * 236.45) - (getCreditHours() * 236.45 * .25)) + "\t" + "(" + (getCreditHours() * 236.45 * .25) + "$ discount applied)");
        }
        else {
            System.out.println("Total payment (after discount): $" + (getCreditHours() * 236.45) + "\t" + "(0$ discount applied)");
        }
        System.out.println("---------------------------------------------------------------------------");
    }
}

//---------------------------------
abstract class Employee extends Person implements Personable {
    private String department;

    public String getDepartment() {
        return department;
    }

    public void setDepartment(String department) {
        this.department = department;
    }

    public Employee() {
        setName("Name not found");
        setId("Id not found");
        department = "Department not found";
    }

    public Employee(String name, String id, String department) {
        setName(name);
        setId(id);
        setDepartment(department);
    }

    public abstract void print();
}

//---------------------------------
class Faculty extends Employee {
    private String rank;

    public String getRank() {
        return rank;
    }

    public void setRank(String rank) {
        this.rank = rank;
    }

    public Faculty() {
        setName("Name not found");
        setId("Id not found");
        setDepartment("Department not found");
        rank = "Rank not found";
    }

    public Faculty(String name, String id, String department, String rank) {
        setName(name);
        setId(id);
        setDepartment(department);
        setRank(rank);
    }

    @Override
    public void print() {
        System.out.println("---------------------------------------------------------------------------");
        System.out.println(getName() + "\t" + getId());
        System.out.println(getDepartment() + ", " + getRank());
        System.out.println("---------------------------------------------------------------------------");
    }
}

//---------------------------------
class Staff extends Employee {
    private String status;

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public Staff() {
        setName("Name not found");
        setId("Id not found");
        setDepartment("Department not found");
        status = "Rank not found";
    }

    public Staff(String name, String id, String department, String status) {
        setName(name);
        setId(id);
        setDepartment(department);
        setStatus(status);
    }

    @Override
    public void print() {
        System.out.println("---------------------------------------------------------------------------");
        System.out.println(getName() + "\t" + getId());
        System.out.println(getDepartment() + ", " + getStatus());
        System.out.println("---------------------------------------------------------------------------");
    }
}
