import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.StringReader;
import java.util.regex.Matcher;
import java.util.regex.Pattern;


/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  @author José Guilherme Vanz
 * */


public class Author{


	public static void main(String[] args){
		System.out.println("Hi! I'm @author annotation remover. Can I do my job? [y]es [n]o");

		new Author().removeAnn(new File(System.getProperty("user.dir")));	
	}

	/**
	 * This method remove all "@author" annotations found in java sources
	 * */
	public void removeAnn(File file){
		if(file.getName().endsWith(".java")){
			try {
				this.removeAnnotationFromFile(file);
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}else if(file.isDirectory()){
			for(File dirFile : file.listFiles()){
				this.removeAnn(dirFile);
			}
		}


	}

	/**
	 * This method remove the "@author" annotations in fact from java sources
	 * @throws IOException 
	 * @parameters The Java Source	
	 */
	private void removeAnnotationFromFile(File source) throws IOException{
		BufferedReader leitor = new BufferedReader(new FileReader(source));
		StringBuilder novoTexto = new StringBuilder();
		if(leitor.ready()){
			String linha = leitor.readLine();
			while(linha != null){
				if(!linha.contains("@author")){
					novoTexto.append(linha);
					novoTexto.append("\n");
				}else{
					System.out.println("Removeu linha com @author - " + source.getName());
				}
				linha = leitor.readLine();
			}
		}
		//remove empty comments
		//REGEX - (/\*[\*|\n]*\*/)
		Pattern.compile("(/\\*[\\*|\n]*\\*/)").matcher(novoTexto).replaceAll("");
		System.out.println("Empties comments removed - " + source.getName());
		File newSource = source.createTempFile(source.getName(), "temp");
		BufferedWriter gravador = new BufferedWriter(new FileWriter(newSource));
		System.out.println(novoTexto.toString());
		gravador.append(novoTexto.toString());
		gravador.flush();
		gravador.close();
		leitor.close();

		newSource.renameTo(source);


	}
}
