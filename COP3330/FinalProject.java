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
        System.out.println("Choose one of the options:");






    }
    public int menu(int option) {
        System.out.println("1 - Enter the information of a faculty");
        System.out.println("2 - Enter the information of a student");
        System.out.println("3 - Print tuition invoice for a student");
        System.out.println("4 - Print faculty information");
        System.out.println("5 - Enter the information of a staff member");
        System.out.println("6 - Print the information of a staff member");
        System.out.println("7 - Delete a person");
        System.out.println("8 - Exit Program");
    }
}
interface Personable {

}
//---------------------------------
abstract class Person implements Personable {

}
//---------------------------------
class Student extends Person {

}
//---------------------------------
abstract class Employee extends Person implements Personable {

}
//---------------------------------
class Faculty extends Employee {

}
//---------------------------------
class Staff extends Employee {

}