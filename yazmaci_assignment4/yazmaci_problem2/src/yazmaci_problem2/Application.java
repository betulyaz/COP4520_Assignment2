package yazmaci_problem2;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Application {

	   public static void main(String[] args) {

	       String dataFile = "problem2.txt";
	       String outputFile = "unique_word_counts.txt";

	       DuplicateCounter duplicateCounter = new DuplicateCounter();

	       try {
	           duplicateCounter.count(dataFile);
	       } catch (IOException e) {
	           e.printStackTrace();
	       }

	       try {
	           duplicateCounter.write(outputFile);
	       } catch (IOException e) {
	           e.printStackTrace();
	       }

	   }

	}