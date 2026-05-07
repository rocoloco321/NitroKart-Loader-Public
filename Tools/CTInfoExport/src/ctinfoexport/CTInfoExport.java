/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package ctinfoexport;

import com.formdev.flatlaf.FlatLightLaf;

/**
 *
 * @author Roco
 */
public class CTInfoExport {

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {

        
        FlatLightLaf.setup();
        java.awt.EventQueue.invokeLater(() -> new MainUI().setVisible(true));
    }
    
}
