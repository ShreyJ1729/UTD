// Shrey Joshi
// SXJ210081

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.ArrayList;

class Main {
    public static void main(String[] args) throws FileNotFoundException {

        // get user input for input file name
        Scanner userInput = new Scanner(System.in);
        String inputFile = userInput.next();
        Scanner fileInput = new Scanner(new File(inputFile));
        userInput.close();

        ArrayList<String> names = new ArrayList<String>();
        ArrayList<String> records = new ArrayList<String>();

        // process data from file to above arrays
        while (fileInput.hasNext()) {
            names.add(fileInput.next());
            records.add(fileInput.next());
        }

        // create arrays for hits, atBats, walks, hbp, plate appearances, strikeouts, and BA/OB to populate with records data
        int[] hits, atBats, walks, hbp, appearances, strikeouts;
        hits = new int[30];
        atBats = new int[30];
        walks = new int[30];
        hbp = new int[30];
        appearances = new int[30];
        strikeouts = new int[30];
        double[] BA = new double[30];
        double[] OB = new double[30];

        // use data in records array to populate the rest
        parseFileDataToArrays(records, hits, atBats, walks, hbp, appearances, strikeouts, BA, OB, names.size());

        // print stats for each person
        printIndividualStats(names, BA, OB, hits, walks, strikeouts, hbp);

        // initalize variables for league leaders
        // we do this in case there are multiple leaders for each statistic
        String BALeaders = "";
        String OBLeaders = "";
        String HLeaders = "";
        String BBLeaders = "";
        String KLeaders = "";
        String HBPLeaders = "";

        // use array data to determine league leaders for each statistic and print it out
        getAndPrintLeagueLeaders(names, BA, OB, hits, walks, strikeouts, hbp, BALeaders, OBLeaders, HLeaders, BBLeaders, KLeaders, HBPLeaders);
    }

    public static void getAndPrintLeagueLeaders(ArrayList<String> names, double[] BA, double[] OB, int[] hits, int[] walks, int[] strikeouts, int[] hbp, String BALeaders, String OBLeaders, String HLeaders, String BBLeaders, String KLeaders, String HBPLeaders) {
        // Calculate league leaders
        // get max element of each array (except K for which we get min)
        int BAiMax = getIndexOfMax(BA, names.size());
        int OBiMax = getIndexOfMax(OB, names.size());
        int HiMax = getIndexOfMax(hits, names.size(), true);
        int BBiMax = getIndexOfMax(walks, names.size(), true);
        int KiMin = getIndexOfMax(strikeouts, names.size(), false);
        int HBPiMax = getIndexOfMax(hbp, names.size(), true);

        // Get names of league leaders --> if there's more than one, a comma and space separates them
        for (int i = 0; i < names.size(); i ++) {
            if (BA[i] == BA[BAiMax]) BALeaders += ", " + names.get(i);
            if (OB[i] == OB[OBiMax]) OBLeaders += ", " + names.get(i);
            if (hits[i] == hits[HiMax]) HLeaders += ", " + names.get(i);
            if (walks[i] == walks[BBiMax]) BBLeaders += ", " + names.get(i);
            if (strikeouts[i] == strikeouts[KiMin]) KLeaders += ", " + names.get(i);
            if (hbp[i] == hbp[HBPiMax]) HBPLeaders += ", " + names.get(i);
        }

        // Print league leaders --> use replaceAll function to remove the comma space at the beginning of the string
        System.out.println("LEAGUE LEADERS");
        System.out.printf("BA: %s %.3f\n", BALeaders.replaceAll("^, ", ""), BA[BAiMax]);
        System.out.printf("OB%%: %s %.3f\n", OBLeaders.replaceAll("^, ", ""), OB[OBiMax]);
        System.out.printf("H: %s %d\n", HLeaders.replaceAll("^, ", ""), hits[HiMax]);
        System.out.printf("BB: %s %d\n", BBLeaders.replaceAll("^, ", ""), walks[BBiMax]);
        System.out.printf("K: %s %d\n", KLeaders.replaceAll("^, ", ""), strikeouts[KiMin]);
        System.out.printf("HBP: %s %d\n", HBPLeaders.replaceAll("^, ", ""), hbp[HBPiMax]);
    }

    // print individual stats for each person
    public static void printIndividualStats(ArrayList<String> names, double[] BA, double[] OB, int[] hits, int[] walks, int[] strikeouts, int[] hbp) {
        // iterate over all names and print individual stats for each person
        for (int i = 0; i < names.size(); i++) {
            System.out.println(names.get(i));
            System.out.printf("BA: %.3f\n", BA[i]);
            System.out.printf("OB%%: %.3f\n", OB[i]);
            System.out.printf("H: %d\n", hits[i]);
            System.out.printf("BB: %d\n", walks[i]);
            System.out.printf("K: %d\n", strikeouts[i]);
            System.out.printf("HBP: %d\n", hbp[i]);
        }
    }

    // takes in records arraylist and processes it to populate the stats arrays
    public static void parseFileDataToArrays(ArrayList<String> records, int[] hits, int[] atBats, int[] walks, int[] hbp, int[] appearances, int[] strikeouts, double[] BA, double[] OB, int length) {
        // iterate over all records of people
        for (int iRecord = 0; iRecord < length; iRecord++) {
            String record = records.get(iRecord);

            // for each record, process characters to each array based on the baseball rules using a switch statement
            for (int j = 0; j < record.length(); j++) {
                char letter = record.charAt(j);
                appearances[iRecord] += 1;
                switch (letter) {
                    case 'H':
                        hits[iRecord]++;
                        atBats[iRecord]++;
                        break;
                    case 'O':
                        atBats[iRecord]++;
                        break;
                    case 'K':
                        atBats[iRecord]++;
                        strikeouts[iRecord]++;
                        break;
                    case 'W':
                        walks[iRecord]++;
                        break;
                    case 'P':
                        hbp[iRecord]++;
                        break;
                    case 'S':
                        break;
                    default:
                        appearances[iRecord] -= 1;
                        break;
                }
            }
        }
        // fill BA and OB arrays using the other statistics
        for (int i = 0; i < length; i++) {
            if (atBats[i]==0) {
                BA[i] = 0.0;
            } else {
                BA[i] = (hits[i] / (double) atBats[i]);
            }
            OB[i] = (hits[i] + walks[i] + hbp[i]) / ((double) appearances[i]);
        }
    }

    // gets index of max element in a double[] array (for OB and BA)
    public static int getIndexOfMax(double[] arr, int length) {
        int iOfMax = 0;
        // iterate over array, updating index if a new max is found
        for (int i = 0; i < length; i++) {
            iOfMax = arr[iOfMax] < arr[i] ? i : iOfMax;
        }
        return iOfMax;
    }
    
    // same overloaded method for int[] arrays
    public static int getIndexOfMax(int[] arr, int length, boolean getMax) {
        int iOfMax = 0;
        for (int i = 0; i < length; i++) {
            if (getMax) {
                iOfMax = arr[iOfMax] < arr[i] ? i : iOfMax;
            } else {
                iOfMax = arr[iOfMax] > arr[i] ? i : iOfMax;
            }
        }
        return iOfMax;
    }
}