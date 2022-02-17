import java.io.*;
import java.io.IOException;
import java.io.InputStream;
import java.io.BufferedReader;
import java.util.List;
import java.util.ArrayList;

public class javashell {
    public static void main(String[] args) throws java.io.IOException {
        String commandLine;
        BufferedReader console = new BufferedReader(new InputStreamReader(System.in));
        while(true){
            System.out.print("jsh>");
            commandLine = console.readLine();
            if(commandLine.equals("exit"))
                break;
            String[] parts = commandLine.split(" ");
            List<String> commandList = new ArrayList<String>();
            for(int i = 0; i < parts.length; i++){
                commandList.add(parts[i]);
            }
        ProcessBuilder pb = new ProcessBuilder(commandList);
        Process proc = pb.start();
        InputStream is = proc.getInputStream();
        InputStreamReader isr = new InputStreamReader(is);
        BufferedReader br = new BufferedReader(isr);
        String line;
        while((line = br.readLine()) !=null)
            System.out.println(line);
        br.close();
        }
    } 
}
