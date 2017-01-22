//
//  ViewController.swift
//  Mattress-X
//
//  Created by dwd on 1/21/17.
//  Copyright © 2017 HoldenDou. All rights reserved.
//

import UIKit
import Charts

class ViewController: UIViewController {
    
    @IBOutlet weak var dayChoosingSegCtrl: UISegmentedControl!
    
    @IBOutlet weak var turnCountBarChart: BarChartView!
    
    @IBOutlet weak var totalScoreBarChart: BarChartView!
        
    @IBAction func segCtrlValueChanged(_ sender: UISegmentedControl) {
        
    }
    
    var sleepEvaluation: String = ""
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        let myurl = NSURL(string: "http://localhost:8080/api")
        let request = NSMutableURLRequest(url: myurl as! URL)
        request.httpMethod = "GET"
        let task = URLSession.shared.dataTask(with: request as URLRequest){
            data, response, error in
            
            // Check for error
            if error != nil
            {
                print("error=\(error)")
                return
            }
            
            // Print out response string

            do {
                if let convertedJsonIntoDict = try JSONSerialization.jsonObject(with: data!, options: []) as? NSDictionary {
                    print(convertedJsonIntoDict)

                    self.sleepEvaluation = (convertedJsonIntoDict["message"] as? String)!
                }
            } catch let error as NSError {
                print(error.localizedDescription)
              }
    }
        task.resume()
        sleepEvaluation = sleepEvaluation.trimmingCharacters(in: .whitespacesAndNewlines)
        let sleepStrQualitySet = sleepEvaluation.components(separatedBy: " ")
        var sleepQualitySet = [Int]()
        for str in sleepStrQualitySet {
            sleepQualitySet.append(Int(str)!)
        }
        print(sleepQualitySet)
        var turnCount = [Int]()
        var totalScore = [Int]()
        for i in 0..<sleepQualitySet.count {
            if(i % 2 == 0) {
                totalScore.append(sleepQualitySet[i])
            }
            else {
                turnCount.append(sleepQualitySet[i])
            }
        }
}

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

