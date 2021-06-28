package main.View;

import java.io.Serializable;
import java.util.*;
import java.util.stream.Collectors;

/**
 * Class to get program outputs
 */
public final class Outputs implements Serializable
{
	/**
	 * Method to clear terminal
	 */
	public static void clear()
	{
		for(int i = 0; i < 100; i++)
			System.out.println();
	}

	/**
	 * Method to get a list formatted as a table
	 * @param list List to Print
	 * @param head_args Sections of the table
	 * @param param Table title
	 * @param time Time that took to complete the query
	 * @param inputs Scanner to get inputs
	 */
	public static void printListAsTable(List<String> list, String[] head_args, String param, Double time, Scanner inputs)
	{
		int max_table_size = 14;
		int args = head_args.length;
		int line_size = 0;

		int[] max_arg_in_line = new int[args];

		for(int i = 0; i < args; i++)
			max_arg_in_line[i] = head_args[i].length();

		for(int i = 0; i < list.size(); i++)
		{
			if(list.get(i).length() > max_arg_in_line[i%args]) 
				max_arg_in_line[i%args] = list.get(i).length();
		}

		for(int i = 0; i < args; i++)
		{
			max_arg_in_line[i] += 11; 
			line_size += max_arg_in_line[i];
		}

		line_size++;

		boolean end = false;

		int pointer = 0, round = 1;

		while(!end)
		{
			clear();
			String page;
			int i, j;

			System.out.println(list.size()/args + " " + param + " fit the criteria.\n");

			printLine(line_size, '-');

			for(i = 0; i < args - 1; i++)
				printTableSpace(head_args[i], max_arg_in_line[i] - 1, false);

			printTableSpace(head_args[i], max_arg_in_line[i] - 1, true);

			for(j = 0; j < max_table_size && pointer < list.size(); j++)
			{
				printLine(line_size, '-');

				for(i = pointer; i%args < args - 1; i++)
					printTableSpace(list.get(i), max_arg_in_line[i%args] - 1, false);

				printTableSpace(list.get(i), max_arg_in_line[i%args] - 1, true);

				pointer += args;
			}

			printLine(line_size, '-');

			System.out.println("Page " + round);

			System.out.println("\nRead " + list.size()/args + " " + param + " in " + time + " s.");

			System.out.println("\nN/n - Next page\nB/b - Previous page\nX/x - Exit\n");

			page = inputs.next();
			page.concat(inputs.nextLine());

			if((page.equals("N") || page.equals("n")) && pointer < list.size())
				round++;

			else if((page.equals("N") || page.equals("n")))
				pointer -= (pointer - ((round - 1) * (max_table_size * args)));

			if((page.equals("B") || page.equals("b")) && round > 1)
			{
				pointer -= (pointer - ((round - 1) * (max_table_size * args)));
				pointer -= max_table_size * args;
				round--;
			}
			else if((page.equals("B") || page.equals("b")) && round == 1)
				pointer = 0;

			if(page.equals("X") || page.equals("x"))
				end = true;
		}
	}

	/**
	 * Method to print Query 5
	 * @param list List to print
	 * @param head_args Sections of the table
	 * @param time Time that took to complete the query
	 * @param inputs Scanner to get inputs
	 */
	public static void printEntryListAsTableQuery5(List<Map.Entry<String, Integer>> list, String[] head_args, double time, Scanner inputs)
	{
		int max_table_size = 14;
		int args = 2;
		int line_size = 0;

		int[] max_arg_in_line = new int[args];

		for(int i = 0; i < args; i++)
			max_arg_in_line[i] = head_args[i].length();

		for(int i = 0; i < list.size(); i++)
		{
			if(list.get(i).getKey().length() > max_arg_in_line[0]) 
				max_arg_in_line[0] = list.get(i).getKey().length();

			if(String.valueOf(list.get(i).getValue()).length() > max_arg_in_line[1]) 
				max_arg_in_line[1] = String.valueOf(list.get(i).getValue()).length();
		}

		for(int i = 0; i < args; i++)
		{
			max_arg_in_line[i] += 11; 
			line_size += max_arg_in_line[i];
		}

		line_size++;

		boolean end = false;

		int pointer = 0, round = 1;

		while(!end)
		{
			clear();
			String page;
			int i, j;

			printLine(line_size, '-');

			for(i = 0; i < args - 1; i++)
				printTableSpace(head_args[i], max_arg_in_line[i] - 1, false);

			printTableSpace(head_args[i], max_arg_in_line[i] - 1, true);

			for(j = 0; j < max_table_size && pointer < list.size(); j++)
			{
				printLine(line_size, '-');

				for(i = 0; i < args - 1; i++)
					printTableSpace(list.get(pointer).getKey(), max_arg_in_line[0] - 1, false);

				printTableSpace(String.valueOf(list.get(pointer).getValue()), max_arg_in_line[1] - 1, true);

				pointer ++;
			}

			printLine(line_size, '-');

			System.out.println("Page " + round);

			System.out.println("\nRead " + list.size() + " entries in " + time + " s.");

			System.out.println("\nN/n - Next page\nB/b - Previous page\nX/x - Exit\n");

			page = inputs.next();
			page.concat(inputs.nextLine());

			if((page.equals("N") || page.equals("n")) && pointer < list.size())
				round++;

			else if((page.equals("N") || page.equals("n")))
				pointer -= (pointer - ((round - 1) * max_table_size));

			if((page.equals("B") || page.equals("b")) && round > 1)
			{
				pointer -= (pointer - ((round - 1) * max_table_size));
				pointer -= max_table_size;
				round--;
			}
			else if((page.equals("B") || page.equals("b")) && round == 1)
				pointer = 0;

			if(page.equals("X") || page.equals("x"))
				end = true;
		}
	}

	/**
	 * Method to print Query 6
	 * @param map Map to print
	 * @param head_args Sections of the table
	 * @param time Time that took to complete the query
	 * @param inputs Scanner to get inputs
	 */
	public static void printMapOfEntryAsTableQuery6(Map<Integer, List<Map.Entry<String, Long>>> map, String[] head_args, double time, Scanner inputs)
	{
		boolean end = false;
		List<Integer> years_aux = map.keySet().stream().collect(Collectors.toList());

		List<Integer> years = years_aux.stream().sorted().collect(Collectors.toList());

		int round = 0;

		int args = 2;

		int[] max_arg_in_line = new int[args];

		while(!end)
		{
			int year = years.get(round);
			
			int line_size = 0;

			for(int i = 0; i < args; i++)
				max_arg_in_line[i] = head_args[i].length();

			for(int i = 0; i < map.get(year).size(); i++)
			{
				if(map.get(year).get(i).getKey().length() > max_arg_in_line[0]) 
					max_arg_in_line[0] = map.get(year).get(i).getKey().length();

				if(String.valueOf(map.get(year).get(i).getValue()).length() > max_arg_in_line[1]) 
					max_arg_in_line[0] = String.valueOf(map.get(year).get(i).getValue()).length();
			}

			for(int i = 0; i < args; i++)
			{
				max_arg_in_line[i] += 11; 
				line_size += max_arg_in_line[i];
			}

			line_size++;
		
			clear();
			String page;
			int i, j;

			printLine(line_size, '-');

			for(i = 0; i < args - 1; i++)
				printTableSpace(head_args[i], max_arg_in_line[i] - 1, false);

			printTableSpace(head_args[i], max_arg_in_line[i] - 1, true);

			for(j = 0; j < map.get(year).size(); j++)
			{
				printLine(line_size, '-');

				for(i = 0; i < args - 1; i++)
					printTableSpace(map.get(year).get(j).getKey(), max_arg_in_line[0] - 1, false);

				printTableSpace(String.valueOf(map.get(year).get(j).getValue()), max_arg_in_line[1] - 1, true);
			}

			printLine(line_size, '-');

			System.out.println("Year " + year);

			System.out.println("\nRead in " + time + " s.");

			System.out.println("\nN/n - Next year\nB/b - Previous year\nX/x - Exit\n");

			page = inputs.next();
			page.concat(inputs.nextLine());

			if((page.equals("N") || page.equals("n")) && round < years.size() - 1)
				round++;

			if((page.equals("B") || page.equals("b")) && round > 0)
				round--;

			if(page.equals("X") || page.equals("x"))
				end = true;
		}
	}

	/**
	 * Method to print a map as a table
	 * @param map Map to print
	 * @param time Time that took to complete the query
	 * @param inputs Scanner to get inputs
	 */
	public static void printMapAsTable(Map<String, List<String>> map, double time, Scanner inputs)
	{
		List<String> heads = map.keySet().stream().collect(Collectors.toList());
		
		boolean end = false;
		int round = 0;

		while(!end)
		{
			String city = heads.get(round);
			int line_size = city.length();

			for(int i = 0; i < map.get(city).size(); i++)
				if(map.get(city).get(i).length() > line_size) line_size = map.get(city).get(i).length();

			line_size += 11;

			clear();
			String page;
			int i;

			printLine(line_size, '-');

			printTableSpace(city,line_size - 1, true);

			for(i = 0; i < map.get(city).size(); i++){
				if(i < map.get(city).size()) printLine(line_size, '-');
				printTableSpace(map.get(city).get(i), line_size - 1, true);
			}

			printLine(line_size, '-');

			System.out.println("\nRead in " + time + " s.");

			System.out.println("\nN/n - Next\nB/b - Previous\nX/x - Exit\n");

			page = inputs.next();
			page.concat(inputs.nextLine());

			if((page.equals("N") || page.equals("n")) && round < heads.size())
				round++;

			if((page.equals("B") || page.equals("b")) && round > 1)
				round--;

			if(page.equals("X") || page.equals("x"))
				end = true;
		}
	}

	/**
	 * Method to print query 8
	 * @param list List to print
	 * @param head_args Sections of the table
	 * @param time Time that took to complete the query
	 * @param inputs Scanner to get inputs
	 */
	public static void printEntryListAsTableQuery8(List<Map.Entry<String, Long>> list, String[] head_args, double time, Scanner inputs)
	{
		int max_table_size = 14;
		int args = 2;
		int line_size = 0;

		int[] max_arg_in_line = new int[args];

		for(int i = 0; i < args; i++)
			max_arg_in_line[i] = head_args[i].length();

		for(int i = 0; i < list.size(); i++)
		{
			if(list.get(i).getKey().length() > max_arg_in_line[0]) 
				max_arg_in_line[0] = list.get(i).getKey().length();

			if(String.valueOf(list.get(i).getValue()).length() > max_arg_in_line[1]) 
				max_arg_in_line[1] = String.valueOf(list.get(i).getValue()).length();
		}

		for(int i = 0; i < args; i++)
		{
			max_arg_in_line[i] += 11; 
			line_size += max_arg_in_line[i];
		}

		line_size++;

		boolean end = false;

		int pointer = 0, round = 1;

		while(!end)
		{
			clear();
			String page;
			int i, j;

			printLine(line_size, '-');

			for(i = 0; i < args - 1; i++)
				printTableSpace(head_args[i], max_arg_in_line[i] - 1, false);

			printTableSpace(head_args[i], max_arg_in_line[i] - 1, true);

			for(j = 0; j < max_table_size && pointer < list.size(); j++)
			{
				printLine(line_size, '-');

				for(i = 0; i < args - 1; i++)
					printTableSpace(list.get(pointer).getKey(), max_arg_in_line[0] - 1, false);

				printTableSpace(String.valueOf(list.get(pointer).getValue()), max_arg_in_line[1] - 1, true);

				pointer ++;
			}

			printLine(line_size, '-');

			System.out.println("Page " + round);

			System.out.println("\nRead in " + time + " s.");

			System.out.println("\nN/n - Next page\nB/b - Previous page\nX/x - Exit\n");

			page = inputs.next();
			page.concat(inputs.nextLine());

			if((page.equals("N") || page.equals("n")) && pointer < list.size())
				round++;

			else if((page.equals("N") || page.equals("n")))
				pointer -= (pointer - ((round - 1) * max_table_size));

			if((page.equals("B") || page.equals("b")) && round > 1)
			{
				pointer -= (pointer - ((round - 1) * max_table_size));
				pointer -= max_table_size;
				round--;
			}
			else if((page.equals("B") || page.equals("b")) && round == 1)
				pointer = 0;

			if(page.equals("X") || page.equals("x"))
				end = true;
		}
	}

	/**
	 * Method to print Query 9
	 * @param list List to print
	 * @param head_args Sections of the table
	 * @param time Time that took to complete the query
	 * @param inputs Scanner to get inputs
	 */
	public static void printEntryListAsTableQuery9(List<Map.Entry<String, Float>> list, String[] head_args, double time, Scanner inputs)
	{
		int max_table_size = 14;
		int args = 2;
		int line_size = 0;

		int[] max_arg_in_line = new int[args];

		for(int i = 0; i < args; i++)
			max_arg_in_line[i] = head_args[i].length();

		for(int i = 0; i < list.size(); i++)
		{
			if(list.get(i).getKey().length() > max_arg_in_line[0]) 
				max_arg_in_line[0] = list.get(i).getKey().length();

			if(String.valueOf(list.get(i).getValue()).length() > max_arg_in_line[1]) 
				max_arg_in_line[1] = String.valueOf(list.get(i).getValue()).length();
		}

		for(int i = 0; i < args; i++)
		{
			max_arg_in_line[i] += 11; 
			line_size += max_arg_in_line[i];
		}

		line_size++;

		boolean end = false;

		int pointer = 0, round = 1;

		while(!end)
		{
			clear();
			String page;
			int i, j;

			printLine(line_size, '-');

			for(i = 0; i < args - 1; i++)
				printTableSpace(head_args[i], max_arg_in_line[i] - 1, false);

			printTableSpace(head_args[i], max_arg_in_line[i] - 1, true);

			for(j = 0; j < max_table_size && pointer < list.size(); j++)
			{
				printLine(line_size, '-');

				for(i = 0; i < args - 1; i++)
					printTableSpace(list.get(pointer).getKey(), max_arg_in_line[0] - 1, false);

				printTableSpace(String.valueOf(list.get(pointer).getValue()), max_arg_in_line[1] - 1, true);

				pointer ++;
			}

			printLine(line_size, '-');

			System.out.println("Page " + round);

			System.out.println("\nRead in " + time + " s.");

			System.out.println("\nN/n - Next page\nB/b - Previous page\nX/x - Exit\n");

			page = inputs.next();
			page.concat(inputs.nextLine());

			if((page.equals("N") || page.equals("n")) && pointer < list.size())
				round++;

			else if((page.equals("N") || page.equals("n")))
				pointer -= (pointer - ((round - 1) * max_table_size));

			if((page.equals("B") || page.equals("b")) && round > 1)
			{
				pointer -= (pointer - ((round - 1) * max_table_size));
				pointer -= max_table_size;
				round--;
			}
			else if((page.equals("B") || page.equals("b")) && round == 1)
				pointer = 0;

			if(page.equals("X") || page.equals("x"))
				end = true;
		}
	}

	/**
	 * Method to print Query 10
	 * @param maps Map to print
	 * @param time Time that took to complete the query
	 * @param inputs Scanner to get inputs
	 */
	public static void printMapsQuery10(Map<String, Map<String, Map<String, Float>>> maps,  double time, Scanner inputs)
	{
		List<String> states = maps.keySet().stream().collect(Collectors.toList());
		
		boolean end_state = false;

		while(!end_state)
		{
			int state_option = -1;

			while(state_option < 0 || state_option > states.size())
			{
				clear();
				printOptionMenu("State", states, false);

				try
				{
					state_option = inputs.nextInt();
					inputs.nextLine();
				}
				catch(InputMismatchException e)
				{
					inputs.nextLine();
				}
			}

			if(state_option != 0)
			{
				String state = states.get(state_option - 1);

				List<String> citys = maps.get(state).keySet().stream().collect(Collectors.toList());

				boolean end_city = false;

				while(!end_city)
				{
					int city_option = -1; 

					while(city_option < 0 || city_option > citys.size())
					{
						clear();
						printOptionMenu("City", citys, false);

						try
						{
							city_option = inputs.nextInt();
							inputs.nextLine();
						}
						catch(InputMismatchException e)
						{
							inputs.nextLine();
						}
					}

					if(city_option != 0)
					{
						String city = citys.get(city_option - 1);

						List<Map.Entry<String,Float>> aux = maps.get(state).get(city).entrySet().stream().collect(Collectors.toList());
						String[] head_args = {"Business ID","Average Grade"};

						printEntryListAsTableQuery9(aux, head_args, time, inputs);
					}
					else
						end_city = true;
				}
			}
			else
				end_state = true;
		}
	}

	/**
	 * Method to print options menu
	 * @param title Title of the menu
	 * @param options List of options
	 * @param isExit Boolean to check if the user want to exit
	 */
	public static void printOptionMenu(String title, List<String> options, boolean isExit)
	{
		int line_size = title.length();

		for(int i = 0; i < options.size(); i++)
		{
			if(options.get(i).length() > line_size) 
				line_size = options.get(i).length();
		}

		line_size += 11;

		clear();
		int j;

		printLine(line_size, '-');

		printTableSpace(title, line_size - 2, true);

		for(j = 0; j < options.size(); j++)
		{
			printLine(line_size, '-');

			printTableSpaceOptioned(options.get(j), line_size - 1, j + 1, true);
		}

		printLine(line_size, '-');

		if(isExit)
			printTableSpaceOptioned("Exit.", line_size - 1, 0, true);

		else printTableSpaceOptioned("Return.", line_size - 1, 0, true);

		printLine(line_size, '-');

		System.out.print("Choose an option: ");
	}

	/**
	 * Auxiliary method to print a line of a char
	 * @param line_size Size of the line to print
	 * @param c Char to print
	 */
	private static void printLine(int line_size, char c)
	{
		for(int i = 0; i < line_size; i++)
			System.out.print(c);

		System.out.println();
	}

	/**
	 * Method to print table space
	 * @param arg Argument of the space
	 * @param max_arg Size of the cell
	 * @param end Boolean indicating if is the end option
	 */
	private static void printTableSpace(String arg, int max_arg, boolean end)
	{
		int spaces = max_arg - arg.length();

		boolean dividable = (spaces%2 == 0);

		System.out.print("|");

		for(int i = 0; i < spaces/2; i++)
			System.out.print(" ");

		System.out.print(arg);

		for(int i = 0; i < spaces/2; i++)
			System.out.print(" ");

		if(!dividable)
			System.out.print(" ");

		if(end)
			System.out.println("|");
	}

	/**
	 * Method to print table space optioned
	 * @param arg Option
	 * @param max_arg Size of the cell
	 * @param option Number of option
	 * @param end Boolean indicating if is the end option
	 */
	private static void printTableSpaceOptioned(String arg, int max_arg, int option, boolean end)
	{
		int spaces = max_arg - arg.length() - String.valueOf(option).length() - 4;

		System.out.print("| ");

		System.out.print(option + ". " + arg);

		for(int i = 0; i < spaces; i++)
			System.out.print(" ");

		if(end)
			System.out.println("|");
	}
}