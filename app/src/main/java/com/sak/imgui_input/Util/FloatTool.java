package com.sak.imgui_input.Util;

import android.content.Context;
import android.util.Log;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class FloatTool {

    public static boolean isRoot() {
        try {
            Process process = Runtime.getRuntime().exec("su");
            OutputStream os = process.getOutputStream();
            os.write("\n".getBytes());
            os.flush();
            os.write("exit".getBytes());
            os.flush();
            os.write("\n".getBytes());
            os.flush();
            int exitValue = process.waitFor();
            os.close();
            return exitValue == 0;
        } catch (Exception e) {
            return false;
        }
    }

    public static byte[] RunShell(String command, boolean isRoot) {
        try {
            Process process = Runtime.getRuntime().exec(isRoot ? "su" : "sh");
            InputStream ins = process.getInputStream();
            InputStream es = process.getErrorStream();
            OutputStream ous = process.getOutputStream();
            ous.write("\n".getBytes());
            ous.flush();
            ous.write(command.getBytes());
            ous.flush();
            ous.write("\n".getBytes());
            ous.flush();
            ous.write("exit".getBytes());
            ous.flush();
            ous.write("\n".getBytes());
            ous.flush();
            byte[] result = readInputStream(ins, false);
            byte[] error = readInputStream(es, false);
            process.waitFor();
            ins.close();
            es.close();
            ous.close();
            if (new String(error).trim().isEmpty()) {
                return result;
            } else {
                return ("Shell Result : \n" + new String(result) + "\n" + "Shell Error : \n" + new String(error) + "\n").getBytes();
            }
        } catch (Throwable th) {
            return ("Application Error : \n" + Log.getStackTraceString(th)).getBytes();
        }
    }

    public static byte[] readInputStream(InputStream ins, boolean close) {
        try {
            ByteArrayOutputStream bos = new ByteArrayOutputStream();
            int i = -1;
            byte[] buf = new byte[1024];
            while ((i = ins.read(buf)) != -1) {
                bos.write(buf, 0, i);
            }
            if (close) {
                ins.close();
                bos.close();
            }
            return bos.toByteArray();
        } catch (Throwable th) {
            return Log.getStackTraceString(th).getBytes();
        }
    }

    public static boolean WriteoutaFile(Context context, String outPath, String fileName) {
        File file = new File(outPath);
        if (!file.exists()) {
            if (!file.mkdirs()) {
                return false;
            }
        }
        
        try {
            InputStream inputStream = context.getAssets().open(fileName);
            File outFile = new File(file, fileName);
            FileOutputStream fileOutputStream = new FileOutputStream(outFile);           
            byte[] buffer = new byte[1024];
            int byteRead;
            while (-1 != (byteRead = inputStream.read(buffer))) {
                fileOutputStream.write(buffer, 0, byteRead);
            }
            inputStream.close();
            fileOutputStream.flush();
            fileOutputStream.close();
            return true;
        } catch (IOException e) {
            e.printStackTrace();
            return false;
        }
    }
}
