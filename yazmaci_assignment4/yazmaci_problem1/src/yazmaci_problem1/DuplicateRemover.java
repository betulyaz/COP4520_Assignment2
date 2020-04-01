package yazmaci_problem1;

import java.util.Scanner;
import java.io.*;
import java.util.Set;
import java.util.HashSet;


public class DuplicateRemover 
{
	Set<String> uniqueWords = new HashSet<>();
	
	public void remove(String dataFile)
	{
		try {
			Scanner input = new Scanner(new File(dataFile));
			
			while (input.hasNext()) 
			{
				String next = input.next().toLowerCase();
				uniqueWords.add(next); 
			}
			
			input.close();
			
		} 
		catch (Exception e) 
		{
			System.out.println("An exception occured!");
		}
	}
	
	public void write(String outputFile) 
	{
		File outFile = new File(outputFile);
		
		try {
			if(!outFile.createNewFile())
			{
				
				PrintStream outFilePrint = new PrintStream(outputFile);
				outFilePrint.println(uniqueWords);
				
				outFilePrint.close();
			}
			else
			{
				
				PrintStream outFilePrint = new PrintStream(outputFile);
				outFilePrint.println(uniqueWords);
				
				outFilePrint.close();
			}
		} 
		catch (Exception e) 
		{
			System.out.println("An exception occured!");
		} 
		
	}
}