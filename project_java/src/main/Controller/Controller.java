package main.Controller;

import main.Model.*;
import main.View.Outputs;

import java.util.*;
import java.util.stream.Collectors;

import java.io.File;
import java.io.IOException;
import java.io.Serializable;
import java.time.LocalDate;
import java.time.Month;

/**
 * Controller Class
 */
public class Controller implements Serializable
{
	/**
	 * Database
	 */
	private GestReviews model;

	/**
	 * Scanner to get all program inputs
	 */
	private Scanner inputs;

	/**
	 * Empty Constructor
	 */
	public Controller()
	{
		this.model = new GestReviews();
		this.inputs = new Scanner(System.in);
	}

	/**
	 * Method to run the app
	 */
	public void run()
	{
		List<String> input_files_menu = new ArrayList<>();
		input_files_menu.add("Manual.");
		input_files_menu.add("Automatic.");

		boolean exit = false;
		int option_read_files = -1;

		while(option_read_files < 0 || option_read_files > input_files_menu.size())
		{
			try
			{
				Outputs.clear();
				Outputs.printOptionMenu("Input Files Menu", input_files_menu, true);
				option_read_files = this.inputs.nextInt();
				this.inputs.nextLine();
			}
			catch(InputMismatchException e)
			{
				this.inputs.nextLine();
			}
		}

		boolean read_files = false;

		switch(option_read_files)
		{
			case 1:
				Outputs.clear();

				System.out.print("Insert path to user information file: ");
				String user_file = this.inputs.next();
				user_file.concat(this.inputs.nextLine());

				Outputs.clear();

				System.out.print("Insert path to business information file: ");
				String business_file = this.inputs.next();
				business_file.concat(this.inputs.nextLine());

				Outputs.clear();

				System.out.print("Insert path to review information file: ");
				String review_file = this.inputs.next();
				review_file.concat(this.inputs.nextLine());

				try
				{
					Outputs.clear();
					System.out.print("Loading files...");
					Crono.start();
					this.model.readUsersFile(user_file);
					this.model.readBusinessesFile(business_file);
					this.model.readReviewsFile(review_file);
					double read_time = Crono.stop();
					read_files = true;

					boolean files_loaded = false;

					while(!files_loaded)
					{
						Outputs.clear();

						System.out.println("Files loaded. Read in " + read_time + " s.");

						System.out.println("\nY/y - continue\n");

						String yes = this.inputs.next();
						yes.concat(this.inputs.nextLine());

						if(yes.equals("Y") || yes.equals("y"))
							files_loaded = true;
					}
				}
				catch(IOException e)
				{
					System.out.println(e.getMessage());
				}
				break;

			case 2:
				try
				{
					Outputs.clear();
					System.out.print("Loading files...");
					Crono.start();
					this.model.readUsersFile("input_files/users_full.csv");
					this.model.readBusinessesFile("input_files/business_full.csv");
					this.model.readReviewsFile("input_files/reviews_1M.csv");
					double read_time = Crono.stop();
					read_files = true;

					boolean files_loaded = false;

					while(!files_loaded)
					{
						Outputs.clear();

						System.out.println("Files loaded. Read in " + read_time + " s.");

						System.out.println("\nY/y - continue\n");

						String yes = this.inputs.next();
						yes.concat(this.inputs.nextLine());

						if(yes.equals("Y") || yes.equals("y"))
							files_loaded = true;
					}
				}
				catch(IOException e)
				{
					System.out.println(e.getMessage());
				}
				break;
				
			case 0:
				exit = true;
				break;
				
			default:
				break;	
		}

		List<String> mainMenuOptions = new ArrayList<>();

		mainMenuOptions.add("Ordered, not reviewed businesses.");
		mainMenuOptions.add("Reviews with month and year.");
		mainMenuOptions.add("User reviews by month.");
		mainMenuOptions.add("Businesses reviews by month.");
		mainMenuOptions.add("User most reviewed businesses.");
		mainMenuOptions.add("X businesses with most reviews by year.");
		mainMenuOptions.add("Three most famous businesses (review-wise) by city.");
		mainMenuOptions.add("X users with most distinct businesses reviewed.");
		mainMenuOptions.add("Business X users with highest grade.");
		mainMenuOptions.add("Business reviews grade average by city, by state.");
		mainMenuOptions.add("Statistics.");
		mainMenuOptions.add("Save database.");
		mainMenuOptions.add("Load database.");

		while(!exit && read_files)
		{
			Outputs.clear();

			Outputs.printOptionMenu("Main Menu", mainMenuOptions, true);

			int option = this.inputs.nextInt();
			this.inputs.nextLine();

			switch(option)
			{
				case 1:
					String[] head_args = {"Businesses_ID"};

					Crono.start();
					List<String> result1 = this.model.getReviewedBusinesses();
					double time1 = Crono.stop();

					Outputs.printListAsTable(result1, head_args, "businesses", time1, this.inputs);
					break;

				case 2:
					int month2 = 0;

					while(month2 < 1 || month2 > 12)
					{
						try
						{
							Outputs.clear();
							System.out.print("Month: ");
							month2 = this.inputs.nextInt();    // TO DO: exeption for when user doen't input integer value 
							this.inputs.nextLine();
						}
						catch(InputMismatchException e)
						{
							this.inputs.nextLine();
						}
					}

					int year2 = -1;

					while(year2 < 2000 || year2 > LocalDate.now().getYear())
					{
						try
						{
							Outputs.clear();
							System.out.print("Year: ");
							year2 = this.inputs.nextInt();					
							this.inputs.nextLine();
						}
						catch(InputMismatchException e)
						{
							this.inputs.nextLine();
						}
					}

					Crono.start();
					Query2Pair result2 = this.model.reviewsByMonth(month2, year2);
					double time2 = Crono.stop();

					boolean cont = false;

					while(!cont)
					{
						Outputs.clear();

						System.out.println(result2.toString());

						System.out.println("\nRead in " + time2 + " s.");

						System.out.println("\nY/y - continue\n");

						String yes = this.inputs.next();
						yes.concat(this.inputs.nextLine());

						if(yes.equals("Y") || yes.equals("y"))
							cont = true;
					}
					break;
					
				case 3:
					Outputs.clear();
					System.out.print("User ID: ");
					String user_id = this.inputs.next();
					user_id.concat(this.inputs.nextLine());

					Crono.start();
					Map<Integer, Query3Triple> result3 = this.model.distinctReviewsUserByMonth(user_id);
					double time3 = Crono.stop();

					boolean end = false;

					int month1 = 1;

					while(!end)
					{
						String page = "";

						Outputs.clear();
						System.out.println("User: " + user_id);
						System.out.println("Month: " + Month.of(month1).name());
						System.out.println(result3.get(month1).toString());

						System.out.println("\nRead in " + time3 + " s.");

						System.out.println("\nN/n - Next\nB/b - Previous\nX/x - Exit\n");

						page = this.inputs.next();
						page.concat(this.inputs.nextLine());

						if((page.equals("N") || page.equals("n")) && month1 < 12)
							month1++;

						if((page.equals("B") || page.equals("b")) && month1 > 1)
							month1--;

						if(page.equals("X") || page.equals("x"))
							end = true;	
					}
					break;
					
				case 4:
					Outputs.clear();
					System.out.print("Business ID: ");
					String business_id = this.inputs.next();
					business_id.concat(this.inputs.nextLine());

					Crono.start();
					Map<Integer, Query4Triple> result4 = this.model.distinctReviewsBusinessByMonth(business_id);
					double time4 = Crono.stop();

					List<Integer> months = result4.keySet().stream().collect(Collectors.toList());

					boolean end4 = false;

					int it = 0;

					while(!end4 && months.size() > 0)
					{
						int month4 = months.get(it);

						String page = "";

						Outputs.clear();
						
						System.out.println("Business: " + business_id);
						System.out.println("Month: " + Month.of(month4).name());
						System.out.println(result4.get(month4).toString());

						System.out.println("\nRead in " + time4 + " s.");

						System.out.println("\nN/n - Next\nB/b - Previous\nX/x - Exit\n");

						page = this.inputs.next();
						page.concat(this.inputs.nextLine());

						if((page.equals("N") || page.equals("n")) && it < months.size() - 1)
							it++;

						if((page.equals("B") || page.equals("b")) && it > 0)
							it--;

						if(page.equals("X") || page.equals("x"))
							end4 = true;	
					}
					break;
					
				case 5:
					Outputs.clear();

					System.out.print("User ID: ");
					String user_id_5 = this.inputs.next();
					user_id_5.concat(this.inputs.nextLine());

					String[] head_args_5 = {"Business Name","Number of Reviews"};

					Crono.start();
					List<Map.Entry<String, Integer>> result5 = this.model.getUserMostReviewedBusinesses(user_id_5);
					double time5 = Crono.stop();

					Outputs.printEntryListAsTableQuery5(result5, head_args_5, time5, this.inputs);
					break;
					
				case 6:
					Outputs.clear();
					System.out.print("Number of businesses to evaluate: ");
					int n6 = this.inputs.nextInt();
					this.inputs.nextLine();

					String[] head_args_6 = {"Business ID","Number of Users"};

					Crono.start();
					Map<Integer, List<Map.Entry<String, Long>>> result6 = this.model.mostReviewedBusinesses(n6);
					double time6 = Crono.stop();

					Outputs.printMapOfEntryAsTableQuery6(result6, head_args_6, time6, this.inputs);
					break;
					
				case 7:
					Crono.start();
					Map<String, List<String>> result7 = this.model.top3BusisByCity();
					double time7 = Crono.stop();

					System.out.println(result7);
					Outputs.printMapAsTable(result7, time7, this.inputs);
					break;
					
				case 8:
					int n8 = 0;

					while(n8 < 1)
					{
						try
						{
							Outputs.clear();
							System.out.print("Number of users to evaluate: ");
							n8 = this.inputs.nextInt();
							this.inputs.nextLine();
						}
						catch(InputMismatchException e)
						{
							this.inputs.nextLine();
						}
					}

					String[] head_args_8 = {"User ID","Number of Businesses"};

					Crono.start();
					List<Map.Entry<String, Long>> result8 = this.model.moreActiveUsers(n8);
					double time8 = Crono.stop();

					Outputs.printEntryListAsTableQuery8(result8, head_args_8, time8, this.inputs);
					break;
					
				case 9:
					Outputs.clear();

					System.out.print("Business ID: ");
					String business_id_9 = this.inputs.next();
					business_id_9.concat(this.inputs.nextLine());

					int n9 = 0;

					while(n9 < 1)
					{
						try
						{
							Outputs.clear();
							System.out.print("Number of users to evaluate: ");
							n9 = this.inputs.nextInt();
							this.inputs.nextLine();
						}
						catch(InputMismatchException e)
						{
							this.inputs.nextLine();
						}
					}

					String[] head_args_9 = {"User ID","Average Grade"};

					Crono.start();
					List<Map.Entry<String, Float>> result9 = this.model.usersWithMoreReviewsOnBusiness(business_id_9, n9);
					double time9 = Crono.stop();

					Outputs.printEntryListAsTableQuery9(result9, head_args_9, time9, this.inputs);
					break;
					
				case 10:
					Crono.start();
					Map<String, Map<String, Map<String, Float>>> result10 = this.model.businessesByStateCityWithAverage();
					double time10 = Crono.stop();

					Outputs.printMapsQuery10(result10, time10, this.inputs);
					break;

				case 11:
					List<String> statiticsMenu = new ArrayList<>();

					statiticsMenu.add("On-read Statistic.");
					statiticsMenu.add("General Statistics.");

					boolean end_statistics = false;

					while(!end_statistics)
					{
						int option_statistics = -1;

						while(option_statistics < 0 || option_statistics > statiticsMenu.size())
						{
							try
							{
								Outputs.clear();
								Outputs.printOptionMenu("Statistics Menu", statiticsMenu, false);
								option_statistics = this.inputs.nextInt();
								this.inputs.nextLine();
							}
							catch(InputMismatchException e)
							{
								this.inputs.nextLine();
							}
						}

						switch(option_statistics)
						{
							case 1:
								Crono.start();
								List<String> last_files 	= this.model.getLastFilesRead();
								int invalid_reviews 		= this.model.getInvalidReviews();
								int businessess_read 		= this.model.getTotalBusinesses();
								int businesses_reviewed 	= this.model.getTotalBusinessesReviewed();
								int businesses_not_reviewed = this.model.getTotalBusinessesNotReviewed();
								int total_users				= this.model.getTotalUsers();
								int users_with_reviews		= this.model.getTotalUsersWithReviews();
								int users_without_reviews	= this.model.getTotalUsersWithoutReviews();
								int reviews_without_impact	= this.model.getTotalReviewsWithoutImpact();
								double stat_time_1 = Crono.stop();

								StringBuilder sb = new StringBuilder();

								sb.append("\nLast read users files: ");
								sb.append(last_files.get(1));
								sb.append("\nLast read businesses files: ");
								sb.append(last_files.get(0));
								sb.append("\nLast read reviews files: ");
								sb.append(last_files.get(2));
								sb.append("\nIt was read ");
								sb.append(invalid_reviews);
								sb.append(" invalid reviews.\nIt was read ");
								sb.append(businessess_read);
								sb.append(" businesses of which ");
								sb.append(businesses_reviewed);
								sb.append(" were reviewed and ");
								sb.append(businesses_not_reviewed);
								sb.append(" weren't.\nIt was read ");
								sb.append(total_users);
								sb.append(" users of which ");
								sb.append(users_with_reviews);
								sb.append(" had made some review and ");
								sb.append(users_without_reviews);
								sb.append(" hadn't.\nThere were ");
								sb.append(reviews_without_impact);
								sb.append(" with no impact at all.\n");

								boolean cont_stat_1 = false;

								while(!cont_stat_1)
								{
									Outputs.clear();

									System.out.println("Read in " + stat_time_1 + " s.\n");

									System.out.println(sb.toString());

									System.out.println("\nY/y - continue\n");

									String yes = this.inputs.next();
									yes.concat(this.inputs.nextLine());

									if(yes.equals("Y") || yes.equals("y"))
									cont_stat_1 = true;
								}
								break;

							case 2:
								List<String> statistics_query2_menu = new ArrayList<>();
								statistics_query2_menu.add("Reviews per month.");
								statistics_query2_menu.add("Average review grade per month.");
								statistics_query2_menu.add("Distinct users that reviewed per month.");

								boolean end_statistics_query2 = false;

								while(!end_statistics_query2)
								{
									int option_statistics_query2 = -1;

									while(option_statistics_query2 < 0 || option_statistics_query2 > statistics_query2_menu.size())
									{
										try
										{
											Outputs.clear();
											Outputs.printOptionMenu("General Statistics Menu", statistics_query2_menu, false);
											option_statistics_query2 = this.inputs.nextInt();
											this.inputs.nextLine();
										}
										catch(InputMismatchException e)
										{
											this.inputs.nextLine();
										}
									}

									switch(option_statistics_query2)
									{
										case 1:
											Crono.start();
											Map<Integer,Integer> stat_result_query2_1 	= this.model.getNReviewsPerMonth();
											double stat_time_2 = Crono.stop();

											List<Integer> stat_query2_months_1 			= stat_result_query2_1.keySet().stream().collect(Collectors.toList());

											boolean stat_query2_end_1 = false;

											int stat_query2_it_1 = 0;

											while(!stat_query2_end_1 && stat_query2_months_1.size() > 0)
											{
												int stat_query2_month_1 = stat_query2_months_1.get(stat_query2_it_1);

												String page = "";

												Outputs.clear();

												System.out.println("Read in " + stat_time_2 + " s.\n");

												System.out.println("Month: " + Month.of(stat_query2_month_1).name());
												System.out.println("Total reviews: " + stat_result_query2_1.get(stat_query2_month_1).toString());

												System.out.println("\nN/n - Next\nB/b - Previous\nX/x - Exit\n");

												page = this.inputs.next();
												page.concat(this.inputs.nextLine());

												if((page.equals("N") || page.equals("n")) && stat_query2_it_1 < stat_query2_months_1.size() - 1)
													stat_query2_it_1++;

												if((page.equals("B") || page.equals("b")) && stat_query2_it_1 > 0)
													stat_query2_it_1--;

												if(page.equals("X") || page.equals("x"))
													stat_query2_end_1 = true;	
											}
											break;

										case 2:
											Crono.start();
											Map.Entry<Float, Map<Integer, Float>> stat_result_query2_2 	= this.model.getAverageClassificationPerMonthAndGlobal();
											double stat_time_3 = Crono.stop();

											List<Integer> stat_query2_months_2 							= stat_result_query2_2.getValue().keySet().stream().collect(Collectors.toList());

											boolean stat_query2_end_2 = false;

											int stat_query2_it_2 = 0;

											while(!stat_query2_end_2 && stat_query2_months_2.size() > 0)
											{
												int stat_query2_month_2 = stat_query2_months_2.get(stat_query2_it_2);

												String page = "";

												Outputs.clear();

												System.out.println("Read in " + stat_time_3 + " s.\n");

												System.out.println("Global average grade: " + stat_result_query2_2.getKey());
												System.out.println("Month: " + Month.of(stat_query2_month_2).name());
												System.out.println("Average grade: " + stat_result_query2_2.getValue().get(stat_query2_month_2).toString());

												System.out.println("\nN/n - Next\nB/b - Previous\nX/x - Exit\n");

												page = this.inputs.next();
												page.concat(this.inputs.nextLine());

												if((page.equals("N") || page.equals("n")) && stat_query2_it_2 < stat_query2_months_2.size() - 1)
													stat_query2_it_2++;

												if((page.equals("B") || page.equals("b")) && stat_query2_it_2 > 0)
													stat_query2_it_2--;

												if(page.equals("X") || page.equals("x"))
													stat_query2_end_2 = true;	
											}
											break;

										case 3:
											Crono.start();
											Map<Integer,Integer> stat_result_query2_3 	= this.model.getDifferentUsersPerMonth();
											double stat_time_4 = Crono.stop();

											List<Integer> stat_query2_months_3 			= stat_result_query2_3.keySet().stream().collect(Collectors.toList());

											boolean stat_query2_end_3 = false;

											int stat_query2_it_3 = 0;

											while(!stat_query2_end_3 && stat_query2_months_3.size() > 0)
											{
												int stat_query2_month_3 = stat_query2_months_3.get(stat_query2_it_3);

												String page = "";

												Outputs.clear();

												System.out.println("Read in " + stat_time_4 + " s.\n");

												System.out.println("Month: " + Month.of(stat_query2_month_3).name());
												System.out.println("Distinct users: " + stat_result_query2_3.get(stat_query2_month_3).toString());

												System.out.println("\nN/n - Next\nB/b - Previous\nX/x - Exit\n");

												page = this.inputs.next();
												page.concat(this.inputs.nextLine());

												if((page.equals("N") || page.equals("n")) && stat_query2_it_3 < stat_query2_months_3.size() - 1)
													stat_query2_it_3++;

												if((page.equals("B") || page.equals("b")) && stat_query2_it_3 > 0)
													stat_query2_it_3--;

												if(page.equals("X") || page.equals("x"))
													stat_query2_end_3 = true;
											}
											break;	
											
										case 0:
											end_statistics_query2 = true;
											break;
											
										default:
											break;	
									}
								}
								break;
	
							case 0:
								end_statistics = true;
								break;
								
							default:
								break;
						}
					}
					break;	
				
				case 12:
					Outputs.clear();

					List<String> save_options = new ArrayList<>();

					save_options.add("Default path.");
					save_options.add("User chosen path.");

					boolean save_end = false;

					while(!save_end)
					{
						int save_option = -1;

						while(save_option < 0 || save_option > save_options.size())
						{
							try
							{
								Outputs.clear();
								Outputs.printOptionMenu("Save Options", save_options, false);
								save_option = this.inputs.nextInt();
								this.inputs.nextLine();
							}
							catch(InputMismatchException e)
							{
								this.inputs.nextLine();
							}
						}

						switch(save_option)
						{
							case 1:
								try
								{
									this.model.saveGestReviewsObject();
									
									boolean files_loaded = false;

									while(!files_loaded)
									{
										Outputs.clear();

										System.out.println("Database was saved at default path file.");

										System.out.println("\nY/y - continue\n");

										String yes = this.inputs.next();
										yes.concat(this.inputs.nextLine());

										if(yes.equals("Y") || yes.equals("y"))
										files_loaded = true;
									}
								}
								catch(IOException e)
								{
									boolean files_loaded = false;

									while(!files_loaded)
									{
										Outputs.clear();

										System.out.println(e.getMessage());

										System.out.println("\nY/y - continue\n");

										String yes = this.inputs.next();
										yes.concat(this.inputs.nextLine());

										if(yes.equals("Y") || yes.equals("y"))
											files_loaded = true;
									}
								}
								break;

							case 2:
								System.out.print("Insert name of object file to save: ");
								String object_file_save = this.inputs.next();
								object_file_save.concat(this.inputs.nextLine());

								try
								{	
									this.model.saveGestReviewsObject(object_file_save);
						
									boolean files_loaded = false;

									while(!files_loaded)
									{
										Outputs.clear();

										System.out.println("Datase was saved at " + object_file_save + ".");

										System.out.println("\nY/y - continue\n");

										String yes = this.inputs.next();
										yes.concat(this.inputs.nextLine());

										if(yes.equals("Y") || yes.equals("y"))
										files_loaded = true;
									}
								}
								catch(IOException e)
								{	
									boolean files_loaded = false;

									while(!files_loaded)
									{
										Outputs.clear();

										System.out.println(e.getMessage());

										System.out.println("\nY/y - continue\n");

										String yes = this.inputs.next();
										yes.concat(this.inputs.nextLine());

										if(yes.equals("Y") || yes.equals("y"))
											files_loaded = true;
									}
								}
								break;
							
							case 0:
								save_end = true;
								break;

							default:
								break;	
						}
					}					
					break;
				
				case 13:
					Outputs.clear();

					File[] files = new File("saves/").listFiles();
					List<String> files_names = new ArrayList<>();

					if(files!= null)
					{
						for(int i = 0; i < files.length; i++)
						{
							files_names.add(files[i].getName());
						}
					}

					int file_option = -1;

					while(file_option < 0 || file_option > files_names.size())
					{
						try
						{
							Outputs.clear();
							Outputs.printOptionMenu("Available Files", files_names, false);
							file_option = this.inputs.nextInt();
							this.inputs.nextLine();
						}
						catch(InputMismatchException e)
						{
							this.inputs.nextLine();
						}
					}

					if(file_option != 0)
					{
						String object_file_load = files_names.get(file_option - 1);

						try
						{
							this.model = this.model.readGestReviewsObject(object_file_load);

							boolean files_loaded = false;

							while(!files_loaded)
							{
								Outputs.clear();

								System.out.println("Datase was loaded from " + object_file_load + ".");

								System.out.println("\nY/y - continue\n");

								String yes = this.inputs.next();
							yes.concat(this.inputs.nextLine());

								if(yes.equals("Y") || yes.equals("y"))
									files_loaded = true;
							}
						}
						catch(Exception e)
						{
							boolean files_loaded = false;

							while(!files_loaded)
							{
								Outputs.clear();

								System.out.println(e.getMessage());

								System.out.println("\nY/y - continue\n");

								String yes = this.inputs.next();
								yes.concat(this.inputs.nextLine());

								if(yes.equals("Y") || yes.equals("y"))
									files_loaded = true;
							}
						}
					}
					break;	
				case 0:
					exit = true;
					break;
					
				default:
					break;	
			}
		}
	}
}