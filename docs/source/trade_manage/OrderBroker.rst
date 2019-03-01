.. currentmodule:: hikyuu.trade_manage
.. highlightlang:: python

订单代理
============

可通过向 :py:meth:`TradeManager.regBroker` 向 TradeManager 注册多个订单代理实例。这些订单代理可执行额外的买入/卖出动作，如邮件订单代理，在 TradeManager 发出买入/卖出指令时，邮件订单代理可以发送邮件。

默认情况下，TradeManager会在执行买入/卖出操作时，调用订单代理执行代理的买入/卖出动作，但这样在实盘操作时会存在问题。因为系统在计算信号指示时，需要回溯历史数据才能得到最新的信号，这样TradeManager会在历史时刻就执行买入/卖出操作， **此时如果订单代理本身没有对发出买入/卖出指令的时刻进行控制，会导致代理发送错误的指令** 。因此，需要指定在某一个时刻之后，才允许执行订单代理的买入/卖出操作。TradeManager的属性 :py:attr:`TradeManager.brokeLastDatetime` 即用于指定该时刻。


Python中的订单代理包装
------------------------

由于通过从 :py:class:`OrderBrokerBase` 继承实现自定义的订单代理，需要实现 _buy、_sell 两个接口方法。由于在 Python 众多的软件包中，有些软件包已经实现了实盘交易的功能，如 Hikyuu 内建的来自 “睿瞳深邃” 的 `扯线木偶 <https://github.com/Raytone-D/puppet>`_  （感谢“睿瞳深邃”的共享）。这些软件包中的交易类一般都已经实现了 buy、sell 方法，如果从 OrderBrokerBase 继承实现订单代理类，代码显得冗长，使用不方便。所以，在 Python 中，实现了 :py:class:`OrderBrokerWrap` 类和 :py:func:`crtOB` 函数，可以快速包装具有 buy、sell 方法的类生成订单代理。代码示例如下::

    #创建模拟交易账户进行回测，初始资金30万
    my_tm = crtTM(initCash = 300000)

    #注册实盘交易订单代理
    my_tm.regBroker(crtOB(TestOrderBroker())) #TestOerderBroker是测试用订单代理对象，只打印
    #my_tm.regBroker(crtOB(Puppet()))  #Puppet为内建的扯线木偶实盘下单对象
    #my_tm.regBroker(crtOB(MailOrderBroker("smtp.sina.com", "yourmail@sina.com", "yourpwd", "receivermail@XXX.yy)))

    #根据需要修改订单代理最后的时间戳，后续只有大于该时间戳时，订单代理才会实际发出订单指令
    my_tm.brokeLastDatetime=Datetime(201706010000)

    #创建信号指示器（以5日EMA为快线，5日EMA自身的10日EMA最为慢线，快线向上穿越慢线时买入，反之卖出）
    my_sg = SG_Flex(OP(EMA(n=5)), slow_n=10)

    #固定每次买入1000股
    my_mm = MM_FixedCount(1000)

    #创建交易系统并运行
    sys = SYS_Simple(tm = my_tm, sg = my_sg, mm = my_mm)
    sys.run(sm['sz000001'], Query(-150))
        

.. py:class:: OrderBrokerWrap(broker[, real=True, slip=0.03])

    订单代理包装类，用户可以参考自定义自己的订单代理，加入额外的处理
    
    :param bool real: 下单前是否重新实时获取实时分笔数据
    :param float slip: 如果当前的卖一价格和指示买入的价格绝对差值不超过slip则下单，否则忽略; 对卖出操作无效，立即以当前价卖出

    .. py:method:: _buy(self, code, price, num)
    
        包装 Python 变量的 buy 方法
        
        :param str code: 证券代码
        :param float price: 买入价格
        :param int num: 买入数量

    .. py:method:: _sell(self, code, price, num)
    
        包装 Python 变量的 sell 方法
        
        :param str code: 证券代码
        :param float price: 卖出价格
        :param int num: 卖出数量
                        

.. py:function:: crtOB(broker[, real=True, slip=0.03]) 

    快速生成订单代理包装对象
    
    :param broker: 订单代理示例，必须拥有buy和sell方法，并且参数为 code, price, num
    :param bool real: 下单前是否重新实时获取实时分笔数据
    :param float slip: 如果当前的卖一价格和指示买入的价格绝对差值不超过slip则下单，否则忽略; 对卖出操作无效，立即以当前价卖出                      
                        
    

内建的订单代理类
------------------    
    
.. py:class:: TestOrderBroker

    用于测试，在执行买入卖出操作时，进行打印，如：“买入：000001 10.0 1000”

.. py:class:: MailOrderBroker

    邮件订单代理，执行买入/卖出操作时发送 Email，如::
        
        my_tm.regBroker(crtOB(MailOrderBroker("smtp.sina.com", "yourmail@sina.com", "yourpwd", "receivermail@XXX.yy)))
    
    .. py:method:: __init__(self, host, sender, pwd, receivers)

        初始化构造函数
        
        :param str host: smtp服务器地址
        :param int port: smtp服务器端口
        :param str sender: 发件邮箱（既用户名）
        :param str pwd: 密码
        :param list receivers: 接受者邮箱列表

    .. py:method:: buy(self, code, price, num)
    
        执行买入操作，向指定的邮箱发送邮件，格式如下:
        
            邮件标题：【Hkyuu提醒】买入 证券代码
            邮件内容：买入：证券代码，价格：买入的价格，数量：买入数量
        
        :param str code: 证券代码
        :param float price: 买入价格
        :param int num: 买入数量
        
        
    .. py:method:: sell(self, code, price, num)
    
        执行卖出操作，向指定的邮箱发送邮件，格式如下:
        
            邮件标题：【Hkyuu提醒】卖出 证券代码
            邮件内容：卖出：证券代码，价格：卖出的价格，数量：卖出数量
    
        :param str code: 证券代码
        :param float price: 卖出价格
        :param int num: 卖出数量
        
   

订单代理基类
----------------

Python中非必须使用 OrderBrokerBase 来实现自定义的订单代理。只要 Python 的对象包含 buy、sell方法，其方法参数规则与 :py:class:`OrderBrokerWrap` 中的 _buy、_sell 方法相同，即可参见前一章节快速创建订单代理实例。

自定义订单代理接口：

* :py:meth:`OrderBrokerBase._buy` - 【必须】执行实际买入操作
* :py:meth:`OrderBrokerBase._sell` - 【必须】执行实际卖出操作


.. py:class:: OrderBrokerBase

    订单代理基类，实现实际的订单操作及程序化的订单
    
    .. py:attribute:: name 代理名称
    
    .. py:method:: __init__(self[, name='NO_NAME'])
    
        初始化订单代理基类
        
        :param str name: 代理名称
        
    .. py:method:: buy(self, code, price, num)

        执行买入操作
    
        :param str code: 证券代码
        :param float price: 买入价格
        :param int num: 买入数量
        :return: 买入操作的执行时刻
        :rtype: Datetime
        
    .. py:method:: sell(self, code, price, num)
    
        执行买入操作
    
        :param str code: 证券代码
        :param float price: 买入价格
        :param int num: 买入数量
        :return: 卖出操作的执行时刻
        :rtype: Datetime

    .. py:method:: _buy(self, code, price, num)

        【重载接口】执行实际买入操作
    
        :param str code: 证券代码
        :param float price: 买入价格
        :param int num: 买入数量
        
    .. py:method:: _sell(self, code, price, num)
    
        【重载接口】执行实际买入操作
    
        :param str code: 证券代码
        :param float price: 买入价格
        :param int num: 买入数量
