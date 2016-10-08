package src;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

import javax.swing.JFileChooser;
import javax.swing.JOptionPane;

public class AnalyzeDefense {
	String TeamNumber;
	int Offense = 0, Defense = 0, HighGoal = 0, LowGoal = 0, Scale = 0, Portcullis = 0, LowBar = 0, ChevalDeFrise = 0,
			Moat = 0, Ramparts = 0, Drawbridge = 0, SallyPort = 0, RockWall = 0, RoughTerrain = 0, team1, team2, team3;
	String line = "", cvsSplitBy = ",";
	BufferedReader br;

	public AnalyzeDefense() {
	}

	public void Analyze() {
		File file = new File("C:\\Users\\rorob\\Desktop");
		final JFileChooser fc = new JFileChooser();
		fc.setCurrentDirectory(file);
		fc.setDialogTitle("Open CSV");
		int returnVal = fc.showOpenDialog(null);
		if (returnVal == JFileChooser.APPROVE_OPTION) {
			file = fc.getSelectedFile();
		} else if (returnVal == JFileChooser.CANCEL_OPTION) {
			System.exit(0);
		}
		Main CSVReader = new Main();
		GetTeamInput();
		AnalyzeCSV(file.getPath());
	}

	public void GetTeamInput() {
		String Team1 = JOptionPane.showInputDialog("Please enter the team number 1");
		if (Team1.equals(null))
			System.exit(1);
		String Team2 = JOptionPane.showInputDialog("Please enter the team number 2: ");
		if (Team2.equals(null))
			System.exit(1);
		String Team3 = JOptionPane.showInputDialog("Please enter the team number 3");
		if (Team3.equals(null))
			System.exit(1);

		team1 = Integer.parseInt(Team1);
		team2 = Integer.parseInt(Team2);
		team3 = Integer.parseInt(Team3);
	}

	public void AnalyzeCSV(String csvFile) {
		try {

			br = new BufferedReader(new FileReader(csvFile));
			while ((line = br.readLine()) != null) {
				String[] term = line.split(cvsSplitBy);
				if (String.valueOf(team1).equals(term[0]) || String.valueOf(team2).equals(term[0])
						|| String.valueOf(team3).equals(term[0])) {

					if (term[1].equals("Offensive"))
						Offense++;
					System.out.println("Offense: " + Offense + "Defense: " + Defense);
					if (term[1].equals("Both")) {
						Offense++;
						Defense++;
					}
					if (term[2].equals("Yes"))
						HighGoal++;
					if (term[3].equals("Yes"))
						LowGoal++;
					if (term[4].equals("Yes"))
						Scale++;

					if (term[5].equals("Yes"))
						Portcullis++;
					if (term[6].equals("Yes"))
						LowBar++;
					if (term[7].equals("Yes"))
						ChevalDeFrise++;
					if (term[8].equals("Yes"))
						Moat++;
					if (term[9].equals("Yes"))
						Ramparts++;
					if (term[10].equals("Yes"))
						Drawbridge++;
					if (term[11].equals("Yes"))
						SallyPort++;
					if (term[12].equals("Yes"))
						RockWall++;
					if (term[13].equals("Yes"))
						RoughTerrain++;

				}

			}
			String data = new String(

					"Offensive: " + Offense + "\nDefensive: " + (3 - Offense) + "\nHigh Goal: " + HighGoal
							+ "\nLow Goal: " + LowGoal + "\nScaling: " + Scale + "\nPortcullis: " + Portcullis
							+ "\nCheval de Frise: " + ChevalDeFrise + "\nLow Bar: " + LowBar + "\nMoat: " + Moat
							+ "\nRamparts: " + Ramparts + "\nDrawbridge: " + Drawbridge + "\nSally Port: " + SallyPort
							+ "\nRock Wall: " + RockWall + "\nRough Terrain: " + RoughTerrain + "\nLow Bar: " + LowBar);
			JOptionPane.showMessageDialog(null, data);

		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (br != null) {
				try {
					br.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}

	}
}
