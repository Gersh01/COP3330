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
abstract class Person {
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

abstract class Employee extends Person {
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
	
	
}

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
