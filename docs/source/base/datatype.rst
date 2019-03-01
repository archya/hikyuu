.. py:currentmodule:: hikyuu
.. highlightlang:: python

基础数据类型
============

日期时间
-----------

.. py:class:: Datetime

    日期时间类（精确到秒），通过以下方式构建：
    
    - 通过字符串：Datetime("2010-1-1 10:00:00")
    - 通过 Python 的date：Datetime(date(2010,1,1))
    - 通过 Python 的datetime：Datetime(datetime(2010,1,1,10)
    - 通过 YYYYMMDDHHMM 形式的整数：Datetime(201001011000)
    
    获取日期列表参见： :py:func:`getDateRange`
    
    获取交易日日期参见： :py:meth:`StockManager.getTradingCalendar` 

    .. py:attribute:: year 年
    .. py:attribute:: month 月
    .. py:attribute:: day 日
    .. py:attribute:: hour 时
    .. py:attribute:: minute 分
    .. py:attribute:: second 秒
    .. py:attribute:: number YYYYMMDDHHMM 形式的整数
    
    .. py:method:: date(self)
    
        转化生成 python 的 date
        
    .. py:method:: datetime(self)
    
        转化生成 python 的datetime
    
    .. py:method:: isNull(self)
    
        是否是Null值, 即是否等于 constant.null_datetime

    .. py:method:: dayOfWeek(self)
    
        返回是一周中的第几天，周日为0，周一为1
        
        :rtype: int
        
    .. py:method:: dateOfWeek(self, day)
    
        返回指定的本周中第几天的日期，周日为0天，周六为第6天
        
        :param int day: 指明本周的第几天，如小于则认为为第0天，如大于6则认为为第6天
        :rtype: Datetime
        
    .. py:method:: dayOfYear(self)
    
        返回一年中的第几天，1月1日为一年中的第1天
        
        :rtype: int
        
    .. py:method:: startOfWeek(self)
    
        返回周起始日期（周一）
        
    .. py:method:: endOfWeek(self)
    
        返回周结束日期（周日）
        
    .. py:method:: startOfMonth(self)
    
        返回月度起始日期
        
    .. py:method:: endOfMonth(self)
    
        返回月末最后一天日期
        
    .. py:method:: startOfQuarter(self)
    
        返回季度起始日期
        
    .. py:method:: endOfQuarter(self)
    
        返回季度结束日期
        
    .. py:method:: startOfHalfyear(self)
    
        返回半年度起始日期
        
    .. py:method:: endOfHalfyear(self)
    
        返回半年度结束日期
        
    .. py:method:: startOfYear(self)
    
        返回年度起始日期
        
    .. py:method:: endOfYear(self)
    
        返回年度结束日期
        
    .. py:method:: nextDay(self)
    
        返回下一自然日
        
    .. py:method:: nextWeek(self)
    
        返回下周周一日期
        
    .. py:method:: nextMonth(self)
    
        返回下月首日日期
        
    .. py:method:: nextQuarter(self)
    
        返回下一季度首日日期
        
    .. py:method:: nextHalfyear(self)
    
        返回下一半年度首日日期
        
    .. py:method:: nextYear(self)
    
        返回下一年度首日日期
        
    .. py:method:: preDay(self)
    
        返回前一自然日日期
        
    .. py:method:: preWeek(self)
    
        返回上周周一日期
        
    .. py:method:: preMonth(self)
    
        返回上月首日日期
        
    .. py:method:: preQuarter(self)
    
        返回上一季度首日日期
        
    .. py:method:: preHalfyear(self)
    
        返回上一半年度首日日期

    .. py:method:: preYear(self)
    
        返回上一年度首日日期
        
    .. py:staticmethod:: max()
    
        获取支持的最大日期时间
        
    .. py:staticmethod:: min()
    
        获取支持的最小日期时间
        
    .. py:staticmethod:: now()
    
        获取当前的日期时间
        
    .. py:staticmethod:: today()
    
        获取当前的日期


K线数据
----------       
       
.. py:class:: KRecord

    K线记录，组成K线数据，属性可读写。
    
    .. py:attribute:: datetime : 日期时间
    .. py:attribute:: openPrice : 开盘价
    .. py:attribute:: highPrice : 最高价
    .. py:attribute:: lowPrice  : 最低价
    .. py:attribute:: closePrice : 收盘价
    .. py:attribute:: transAmount : 成交金额
    .. py:attribute:: transCount: 成交量

    
.. py:class:: KData

    通过 Stock.getKData 获取的K线数据，由 KRecord 组成的数组，可象 list 一样进行遍历
    
    .. py:attribute:: startPos
    
        获取在原始K线记录中对应的起始位置，如果KData为空返回0
        
    .. py:attribute:: lastPos
    
        获取在原始K线记录中对应的最后一条记录的位置，如果为空返回0,其他等于endPos - 1
        
    .. py:attribute:: endPos
    
        获取在原始K线记录中对应范围的下一条记录的位置，如果为空返回0,其他等于lastPos + 1
        
    .. py:method:: size()
    
        K线记录数量，同 __len__
    
    .. py:method:: getDatetimeList()
    
        返回交易日期列表

        :rtype: DatetimeList
        
    .. py:method:: getKRecord(pos)
    
        获取指定索引位置的K线记录
        
        :param int pos: 位置索引
        :rtype: KRecord
        
    .. py:method:: get(pos)

        同 :py:meth:`KData.getKRecord`。获取指定索引位置的K线记录
        
        :param int pos: 位置索引
        :rtype: KRecord        
    
    .. py:method:: getKRecordByDate(datetime)

        获取指定时间的K线记录
    
        :param Datetime datetime: 指定的日期
        :rtype: KRecord
        
    .. py:method:: getByDate(datetime)    

        获取指定时间的K线记录。同 getKRecordByDate。
    
        :param Datetime datetime: 指定的日期
        :rtype: KRecord
    
    .. py:method:: getPos(datetime)

        获取指定时间对应的索引位置
        
        :param Datetime datetime: 指定的时间
        :return: 对应的索引位置，如果不在数据范围内，则返回 None    
    
    .. py:method:: empty()
    
        判断是否为空
    
        :rtype: bool
    
    .. py:method:: getQuery()
    
        获取关联的查询条件
    
        :rtype: KQuery
    
    .. py:method:: getStock()
    
        获取关联的Stock
    
        :rtype: Stock
    
    .. py:method:: tocsv(filename)
    
        将数据保存至CSV文件
    
        :param str filename: 指定保存的文件名称

    .. py:method:: to_np()
    
        转化为numpy结构数组
    
        :rtype: numpy.array
        
    .. py:method:: to_df()
    
        转化为pandas的DataFrame
        
        :rtype: pandas.DataFrame


分时线数据
--------------

.. py:class:: TimeLineRecord

    分时线记录，属性可读写。
    
    .. py:attribute:: datetime : 时间
    .. py:attribute:: price : 价格
    .. py:attribute:: vol : 成交量


.. py:class:: TimeLineList

    通过 Stock.getTimeLineList 获取的分时线数据，由 TimeLineRecord 组成的数组，可象 list 一样进行遍历
    
    .. py:method:: to_np()
    
        转化为numpy结构数组
    
        :rtype: numpy.array
        
    .. py:method:: to_df()
    
        转化为pandas的DataFrame
        
        :rtype: pandas.DataFrame
        

分笔历史数据
----------------

.. py:class:: TransRecord

    历史分笔数据记录
    
    .. py:attribute:: datetime : 时间
    .. py:attribute:: price : 价格
    .. py:attribute:: vol : 成交量
    .. py:attribute:: direct : 买卖盘性质
    
.. py:class:: TransList

    分时线数据列表
    
    .. py:method:: to_np()
    
        转化为numpy结构数组
    
        :rtype: numpy.array
        
    .. py:method:: to_df()
    
        转化为pandas的DataFrame
        
        :rtype: pandas.DataFrame
    
