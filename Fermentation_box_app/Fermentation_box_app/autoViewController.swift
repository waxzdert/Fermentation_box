//
//  ViewController.swift
//  Fermentation_box_app
//
//  Created by 吳東燁 on 2018/2/24.
//  Copyright © 2018年 吳東燁. All rights reserved.
//

import UIKit

class autoViewController: UIViewController {
    
    @IBOutlet weak var tempPicker: UIPickerView!
    @IBOutlet weak var timePicker: UIPickerView!
    
    var temp: [String] = []
    var time: [String] = []
    
    var temp: Int = 1
    var time: Int = 1
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        //製作溫度和時間陣列
        var i:Int
        for i = 1; i <= 100; i++ {
            months.append("\(i)")
        }
        for i = 1; i <= 24; i++ {
            days.append("\(i)")
        }
        
        
        
        
        
        
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
}


