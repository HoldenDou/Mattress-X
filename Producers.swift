//
//  File.swift
//  Mattress-X
//
//  Created by dwd on 1/21/17.
//  Copyright © 2017 HoldenDou. All rights reserved.
//

import Foundation
import Charts

let xlegend: [String] = ["6d", "5d", "4d", "3d", "2d", "yesterday", "today"]


func toActualDays(segNumOfDays: Int, dataSource: [Int]) -> Int{
    var actualNumOfDays: Int = 0
    switch segNumOfDays {
    case 0: // One week
        actualNumOfDays = (dataSource.count >= 7) ? 7 : dataSource.count
    case 1: // 5 days
        actualNumOfDays = (dataSource.count >= 5) ? 5 : dataSource.count
    case 2: // 3 days
        actualNumOfDays = (dataSource.count >= 3) ? 3 : dataSource.count
    case 3: // today
        actualNumOfDays = (dataSource.count >= 1) ? 1 : dataSource.count
    default:
        break
    }
    return actualNumOfDays
}

func turnCountDataProduce(numOfDays: Int, dataSource: [Int]) -> BarChartData {
    // numOfDays are in fact 0, 1, 2, 3 from segmented control
    let actualNumOfDays: Int = toActualDays(segNumOfDays: numOfDays, dataSource: dataSource)
    var turnDataEntries = [ChartDataEntry]()
    
    var i = 0
    
    for turnCount in dataSource {
        let turnEntry = BarChartDataEntry(x: Double(i), y: Double(dataSource[i]), data: xlegend as AnyObject?)
        i += 1
    }
    
    
    
}
