package src;

import javax.swing.JOptionPane;

public class Main {
	public static void main(String[] args) {
		AnalyzeDefense Analyzer = new AnalyzeDefense();
		Scouter Scout = new Scouter();
		Object options[] = { "Scout", "Analyze" };
		int mode = JOptionPane.showOptionDialog(null, "Would you like to scout or analyze?", "Scouting 263",
				JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, options, null);
		if (mode == 0)
			Scout.Scout();
		else if (mode == 1)
			Analyzer.Analyze();
	}

}
