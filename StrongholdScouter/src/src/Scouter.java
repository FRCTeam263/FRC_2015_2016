package src;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

import javax.rmi.CORBA.Util;
import javax.swing.JOptionPane;
import javax.swing.plaf.FileChooserUI;
import javax.swing.text.Utilities;
import javax.xml.stream.events.EndDocument;

public class Scouter {
	private static final String ScoutingFile = new String("C:\\Users\\rorob\\Desktop\\ScoutingTest.csv");
	BufferedWriter bw;
	BufferedReader br;
	File file = new File(ScoutingFile);
	String[] Options2 = new String[] { "Log And Exit", "Log And Continue", "Dont Log And Exit" };
	String[] Options = new String[] { "Offensive", "Defensive", "Both" };
	String Comma = new String(",");
	String Data[], InitLine, TeamNumber, Strategy, HighGoal, LowGoal, Scale, Portcullis, LowBar, Cheval, Moat, Ramparts,
			Sally, Drawbridge, Rock, Rough;
	int strategy, highGoal, lowGoal, scale, portcullis, lowBar, cheval, moat, ramparts, sally, drawbridge, rock, rough;

	public Scouter() {
		if (!file.exists()) {
			try {
				file.createNewFile();
			} catch (IOException e) {
				System.out.println("Something Messed Up");
			}
		}
	}

	/*
	 * while ((InitLine = br.readLine()) != null) { String[] Data =
	 * InitLine.split(","); GetData(); }
	 */
	public void Scout() {
		GetData();
		LogData();
	}

	public void GetData() {
		TeamNumber = JOptionPane.showInputDialog("Please Enter The Team Number");
		if (TeamNumber.equals(null))
			System.exit(1);
		strategy = JOptionPane.showOptionDialog(null, "Are They Offensive Or Defensive?", "Scouting 263", 0, 0, null,
				Options, null);
		if (strategy == -1)
			System.exit(1);
		highGoal = JOptionPane.showConfirmDialog(null, "Can They Shoot High Goal?", "Scouting 263",
				JOptionPane.YES_NO_OPTION);
		if (highGoal == -1)
			System.exit(1);
		lowGoal = JOptionPane.showConfirmDialog(null, "Can They Shoot Low Goal?", "Scouting 263",
				JOptionPane.YES_NO_OPTION);
		if (lowGoal == -1)
			System.exit(1);
		scale = JOptionPane.showConfirmDialog(null, "Can They Scale The Tower?", "Scouting 263",
				JOptionPane.YES_NO_OPTION);
		if (scale == -1)
			System.exit(1);
		portcullis = JOptionPane.showConfirmDialog(null, "Can They Cross The Portcullis?", "Scouting 263",
				JOptionPane.YES_NO_OPTION);
		if (portcullis == -1)
			System.exit(1);
		lowBar = JOptionPane.showConfirmDialog(null, "Can They Cross The Low Bar?", "Scouting 263",
				JOptionPane.YES_NO_OPTION);
		if (lowBar == -1)
			System.exit(1);
		cheval = JOptionPane.showConfirmDialog(null, "Can They Cross The Cheval de Frise?", "Scouting 263",
				JOptionPane.YES_NO_OPTION);
		if (cheval == -1)
			System.exit(1);
		moat = JOptionPane.showConfirmDialog(null, "Can They Cross The Moat?", "Scouting 263",
				JOptionPane.YES_NO_OPTION);
		if (moat == -1)
			System.exit(1);
		ramparts = JOptionPane.showConfirmDialog(null, "Can They Cross The Ramparts?", "Scouting 263",
				JOptionPane.YES_NO_OPTION);
		if (ramparts == -1)
			System.exit(1);
		drawbridge = JOptionPane.showConfirmDialog(null, "Can They Cross The Drawbridge?", "Scouting 263",
				JOptionPane.YES_NO_OPTION);
		if (drawbridge == -1)
			System.exit(1);
		sally = JOptionPane.showConfirmDialog(null, "Can They Cross The Sally Port?", "Scouting 263",
				JOptionPane.YES_NO_OPTION);
		if (sally == -1)
			System.exit(1);
		rock = JOptionPane.showConfirmDialog(null, "Can They Cross The Rock Wall?", "Scouting 263",
				JOptionPane.YES_NO_OPTION);
		if (rock == -1)
			System.exit(1);
		rough = JOptionPane.showConfirmDialog(null, "Can They Cross The Rough Terrain?", "Scouting 263",
				JOptionPane.YES_NO_OPTION);
		if (rough == -1)
			System.exit(1);

		ParseData();
		Data = new String[] { TeamNumber, Strategy, HighGoal, LowGoal, Scale, Portcullis, LowBar, Cheval, Moat,
				Ramparts, Drawbridge, Sally, Rock, Rough };
	}

	public void LogData() {
		int task = JOptionPane.showOptionDialog(null, "What Do You Want To Do Now", "Scouting 263", 0, 0, null,
				Options2, null);
		if (task == 2)
			System.exit(1);
		try {
			bw = new BufferedWriter(new FileWriter(ScoutingFile, true));
			br = new BufferedReader(new FileReader(ScoutingFile));
			/*
			 * while ((InitLine = br.readLine()) != null) { int x =
			 * Integer.parseInt(InitLine.split(",")[0]); int y =
			 * Integer.parseInt(TeamNumber); if (y > x) {
			 * 
			 * }
		*/
			List<String> newCSV = Files.readAllLines(file.toPath());
			for (int x = 0; x < newCSV.size(); x++) {
				bw.append(newCSV.get(x));
			}
a
			bw.flush();
			bw.close();
		} catch (FileNotFoundException e) {
			System.out.println("File Not Found");
		} catch (IOException e) {
			System.out.println("Something Messed Up");
		}
		if (task == 1)
			Scout();
	}

	// val = Options == 0 ? "Yes" : "No";
	public void ParseData() {
		switch (strategy) {
		case 0:
			Strategy = "Offensive";
			break;
		case 1:
			Strategy = "Defensive";
			break;
		case 2:
			Strategy = "Both";
			break;
		default:
			Strategy = null;
			break;
		}
		HighGoal = highGoal == 0 ? "Yes" : "No";
		LowGoal = lowGoal == 0 ? "Yes" : "No";
		Scale = scale == 0 ? "Yes" : "No";
		Portcullis = portcullis == 0 ? "Yes" : "No";
		LowBar = lowBar == 0 ? "Yes" : "No";
		Cheval = cheval == 0 ? "Yes" : "No";
		Moat = moat == 0 ? "Yes" : "No";
		Ramparts = ramparts == 0 ? "Yes" : "No";
		Drawbridge = drawbridge == 0 ? "Yes" : "No";
		Sally = sally == 0 ? "Yes" : "No";
		Rock = rock == 0 ? "Yes" : "No";
		Rough = rough == 0 ? "Yes" : "No";
	}

}
