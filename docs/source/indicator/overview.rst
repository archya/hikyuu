.. py:currentmodule:: hikyuu.indicator
.. highlightlang:: python

技术指标总览
============

**K线类指标**

* :py:func:`KDATA` - 包装KData成Indicator，用于其他指标计算
* :py:func:`KDATA_PART` - 根据字符串选择返回指标KDATA/OPEN/HIGH/LOW/CLOSE/AMO/VOL
* :py:func:`OPEN`  - 包装KData的开盘价成Indicator
* :py:func:`HIGH`  - 包装KData的最高价成Indicator
* :py:func:`LOW`   - 包装KData的最低价成Indicator
* :py:func:`CLOSE` - 包装KData的收盘价成Indicator
* :py:func:`AMO`   - 包装KData的成交金额成Indicator
* :py:func:`VOL`   - 包装KData的成交量成Indicator
    

   
**辅助类指标**

* :py:func:`PRICELIST` - 将PriceList或Indicator的结果集包装为Indicator
* :py:func:`ABS` - 求绝对值
* :py:func:`BETWEEN` - 介于(介于两个数之间)
* :py:func:`CEILING` - 向上舍入(向数值增大方向舍入)取整
* :py:func:`CVAL` - 创建指定长度的固定数值指标
* :py:func:`COUNT` - 统计满足条件的周期数
* :py:func:`DIFF` - 差分指标，即data[i] - data[i-1]
* :py:func:`EXP` - e的X次幂
* :py:func:`FLOOR` - 向下舍入(向数值减小方向舍入)取整
* :py:func:`HHV` - N日内最高价
* :py:func:`HHVBARS` - 上一高点位置 求上一高点到当前的周期数
* :py:func:`IF` - 根据条件求不同的值
* :py:func:`LLV` - N日内最低价
* :py:func:`LLVBARS` - 上一低点位置 求上一低点到当前的周期数
* :py:func:`MAX` - 最大值
* :py:func:`MIN` - 最小值
* :py:func:`NOT` - 求逻辑非
* :py:func:`POW` - 乘幂
* :py:func:`REF` - 向前引用 （即右移），引用若干周期前的数据
* :py:func:`ROUND` - 四舍五入
* :py:func:`ROUNDUP` -  向上截取，如10.1截取后为11
* :py:func:`ROUNDDOWN` - 向下截取，如10.1截取后为10
* :py:func:`SGN` - 求符号值
* :py:func:`SQRT` - 开平方
* :py:func:`STDEV` - 计算N周期内样本标准差
* :py:func:`WEAVE` - 将两个ind的结果合并到一个ind中



**叠加类指标（Overlap Studies）**

* :py:func:`MA`  - 移动平均数包装，默认为简单平均数
* :py:func:`AMA` - 佩里.J 考夫曼（Perry J.Kaufman）自适应移动平均 [BOOK1]_
* :py:func:`EMA` - 指数移动平均线(Exponential Moving Average)
* :py:func:`SMA` - 简单移动平均线
* :py:func:`SAFTYLOSS` - 亚历山大 艾尔德安全地带止损线

    
**动量类指标（Momentum Indicators）**

* :py:func:`MACD` - 平滑异同移动平均线
* :py:func:`VIGOR` - 亚历山大.艾尔德力度指数


**成交量类指标（Volume Indicators）**


**波动类指标（Volatility Indicators）**


**价格转换类指标（Price Transform）**


**周期类指标（Cycle Indicators）**


**模式识别类指标（Pattern Recognition）**
