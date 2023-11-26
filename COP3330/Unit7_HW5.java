//Unit7_HW5
//Alexander Gershfeld
//Hatim Boustique
//COP3330
//November 19, 2023

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws FileNotFoundException {
        //file IO
        PrintWriter writer = new PrintWriter("lecturesOnly.txt");
        Scanner fileInput = new Scanner(new File("C:\\Users\\Alex\\IdeaProjects\\Unit7_HW_5\\src\\lec.txt"));
        Scanner userInput = new Scanner(System.in);

        List<String> courses = new ArrayList<String>();
        String line;
        String [] itemized;
        int count = 0;

        //start writing in file
        writer.println("Online Lectures");
        while(fileInput.hasNextLine()) {
            //process the input
            line = fileInput.nextLine();
            itemized = line.split(",");
            courses.add(line);

            try {
                //if the course is online increment the counter and write to file the online course
                if (itemized[4].compareToIgnoreCase("online") == 0) {
                    writer.println(line);
                    count++;
                }
            }
            catch(Exception e) { //if the course is a lab continue
                continue;
            }
        }

        //output final count of online lectures offered
        System.out.println("There are " + count + " online lectures offered");

        System.out.print("Enter the classroom: ");
        String user = userInput.nextLine();

        //print half of the correct output
        System.out.print("The crns held in " + user + " are: ");

        //the rest of the output is determined in this for loop
        for(String course: courses) {
            itemized = course.split(",");
            try {
                //if the classroom matches with regular courses, print it
                if(itemized[5].compareToIgnoreCase(user) == 0)
                    System.out.print(itemized[0] + " ");
            }
            catch(ArrayIndexOutOfBoundsException a) {
                //if the classroom matches with labs, print it
                if (itemized[1].compareToIgnoreCase(user) == 0)
                    System.out.print(itemized[0] + " ");
            }
        }

        //start the next section of the file
        writer.println("\nLectures with No Lab");
        for(String course: courses) {
            itemized = course.split(",");
            try {
                //if the course is not a lab and does not have any labs, print to file
                if(itemized[6].compareToIgnoreCase("no") == 0)
                    writer.println(course);
            }
            catch(ArrayIndexOutOfBoundsException a) {
                continue;
            }
        }

        System.out.println("\nlecturesOnly.txt is created\nGoodbye!");
        writer.close();
    }
}
