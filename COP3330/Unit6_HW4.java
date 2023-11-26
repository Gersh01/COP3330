//Unit6_HW4
//Alexander Gershfeld
//Hatim Boustique
//COP3330

import java.util.Scanner;

public class DriverClass {
    public static void main(String[] args) {
        int numRows, numColumns;
        int index, start, end;
        char charAtIndex;
        int length;
        String subSequence;

        Scanner myScan = new Scanner(System.in);

        System.out.print("Enter how many rows and how many columns to load: ");
        numRows = myScan.nextInt();
        numColumns = myScan.nextInt();

        Code codeObject = new Code(numRows, numColumns);

        codeObject.loadCodeArray(numRows, numColumns);
        codeObject.printCodeArray(numRows, numColumns);
        //____________________________________________________________
        System.out.print("\n\nTesting charAt: Enter your index [a number greater or equal to 0" +
                "and less or equal to ");
        System.out.print((numRows*numColumns-1) + "]: ");
        index = myScan.nextInt();

        charAtIndex = codeObject.charAt(index);

        System.out.println("The character located at index " + index + " is: " + charAtIndex);

        //____________________________________________________________
        length = codeObject.length();

        System.out.println("\n\nTesting length: there are " + length + " characters.");

        //____________________________________________________________
        System.out.print("\n\nTesting subSequence: Enter start and end indices: ");

        start = myScan.nextInt();
        end = myScan.nextInt();

        subSequence = codeObject.subSequence(start, end);
        System.out.println("The subSequence is: " + subSequence);

        //____________________________________________________________
        System.out.println("\nGoodbye!");
    }


}
//____________________________________________________________
class Code implements CharSequence {
    private int[][] codeArray;
    private int numRows, numColumns;

    public Code(int numRows, int numColumns) {
        this.numRows = numRows;
        this.numColumns = numColumns;
        codeArray = new int[numRows][numColumns];
    }

    public void loadCodeArray(int numRows, int numColumns) {
        Scanner myScan = new Scanner(System.in);
        int i, j;
        for(i = 0; i < numRows; i++) {
            System.out.print("Enter Row " + (i+1) + ": ");
            for(j = 0; j < numColumns; j++) {
                codeArray[i][j] = myScan.nextInt();
            }
        }
    }

    public void printCodeArray(int numRows, int numColumns) {
        int i, j;
        System.out.println("\n_____________\n");
        for(i = 0; i < numRows; i++) {
            for(j = 0; j < numColumns; j++) {
                System.out.print(codeArray[i][j] + "\t");
            }
            System.out.println("");
        }
    }

    @Override
    public char charAt(int index) {
        //floor value decides which row of the 2D array to access
        int row = index / numColumns;
        //the remainder of the index indicates which column to access
        int col = index % numColumns;

        //casting the value at the index returns the ascii conversion
        return (char)codeArray[row][col];
    }

    @Override
    public int length() {
        //counts the amount of valid entries inside of the array
        int counter = 0;

        //iterates through the whole 2D array to see if each entry is a valid ascii code
        for(int i = 0; i < numRows; i++)
            for(int j = 0; j < numColumns; j++)
                if(codeArray[i][j] >= 0 && codeArray[i][j] < 256)
                    counter++;

        return counter;
    }

    @Override
    public String subSequence(int start, int end) {
        //The size of the sub string is determined
        int size = (end - start) + 1;

        //the substring starts as a character array
        char [] tmp = new char[size];

        //the character array is converted into this string
        String retString;

        for(int i = 0; i < size; i++) {
            //the tmp array is initialized to the character at the index
            tmp[i] = charAt(start);

            //the indices from start to end are accessed by adding until the size is met
            start++;
        }

        //the values of the character array are converted into a string to then get returned
        retString = String.valueOf(tmp);
        return retString;
    }
}
