#include <view/ImGui/MessageConsole.h>
#include <core/Application.h>
#include <view/UIEvents.h>

namespace Forged::View
{

MessageConsole::MessageConsole(IServiceLocator& services)
: mServices(services)
, mAutoScroll(true)
, mOpen(true)
{
    clear();
}

void MessageConsole::onInitialize()
{
    // mServices.getReactiveService().subscribeToLogMessage([&](const std::string& message)
    // {
    //     addLog(message.c_str());
    // });

    mServices.getEventBus().getEvent<Events::TraceMessageEvent>().subscribe([&](auto event)
    {
        addLog(event.message.c_str());
    },
    [](std::exception_ptr eptr)
    {
        try 
        {
            std::rethrow_exception(eptr);
        }
        catch (const std::exception& ex) 
        {
            std::cout << "OnError: " << ex.what() << std::endl;
        }
    }, []()
    {
        // on complete
    });


    // rxcpp::subjects::subject<std::any> subject;

    // subject.get_observable().filter([](std::any any)
    // {
    //     return std::any_cast<Events::TraceMessageEvent*>(any) != nullptr;
    // })
    // .map([](std::any any)
    // {
    //     return *std::any_cast<Events::TraceMessageEvent*>(any);
    // });

    // subject.get_observable().subscribe([](std::any any)
    // {
        
    // });

    // subject.get_subscriber().on_next(Events::TraceMessageEvent{Events::LogLevel::Error, ""});
}

void MessageConsole::onShutdown() 
{
}

void MessageConsole::clear()
{
    mBuf.clear();
    mLineOffsets.clear();
    mLineOffsets.push_back(0);
}

void MessageConsole::addLog(const char* fmt, ...) IM_FMTARGS(2)
{
    int old_size = mBuf.size();
    va_list args;
    va_start(args, fmt);
    mBuf.appendfv(fmt, args);
    va_end(args);

    mLineOffsets.push_back(mBuf.size());

    // for (int new_size = mBuf.size(); old_size < new_size; old_size++)
    // {
    //     if (mBuf[old_size] == '\n')
    //     {
    //         mLineOffsets.push_back(old_size + 1);
    //     }
    // }
}

void MessageConsole::onDraw()
{
    if (!mOpen)
    {
        return;
    }

    if (!ImGui::Begin("Message Console", &mOpen))
    {
        ImGui::End();
        return;
    }

    // Options menu
    if (ImGui::BeginPopup("Options"))
    {
        ImGui::Checkbox("Auto-scroll", &mAutoScroll);
        ImGui::EndPopup();
    }

    // Main window
    if (ImGui::Button("Options"))
    {
        ImGui::OpenPopup("Options");
    }

    ImGui::SameLine();
    bool clearButton = ImGui::Button("Clear");
    ImGui::SameLine();
    bool copy = ImGui::Button("Copy");
    ImGui::SameLine();
    mFilter.Draw("Filter", -100.0f);

    ImGui::Separator();

    if (ImGui::BeginChild("scrolling", ImVec2(0, 0), ImGuiChildFlags_None, ImGuiWindowFlags_HorizontalScrollbar))
    {
        if (clearButton)
        {
            clear();
        }

        if (copy)
        {
            ImGui::LogToClipboard();
        }

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        const char *buf = mBuf.begin();
        const char *buf_end = mBuf.end();
        if (mFilter.IsActive())
        {
            // In this example we don't use the clipper when Filter is enabled.
            // This is because we don't have random access to the result of our filter.
            // A real application processing logs with ten of thousands of entries may want to store the result of
            // search/filter.. especially if the filtering function is not trivial (e.g. reg-exp).
            for (int line_no = 0; line_no < mLineOffsets.Size; line_no++)
            {
                const char *line_start = buf + mLineOffsets[line_no];
                const char *line_end = (line_no + 1 < mLineOffsets.Size) ? (buf + mLineOffsets[line_no + 1] - 1) : buf_end;
                if (mFilter.PassFilter(line_start, line_end))
                {
                    ImGui::TextUnformatted(line_start, line_end);
                }
            }
        }
        else
        {
            // The simplest and easy way to display the entire buffer:
            //   ImGui::TextUnformatted(buf_begin, buf_end);
            // And it'll just work. TextUnformatted() has specialization for large blob of text and will fast-forward
            // to skip non-visible lines. Here we instead demonstrate using the clipper to only process lines that are
            // within the visible area.
            // If you have tens of thousands of items and their processing cost is non-negligible, coarse clipping them
            // on your side is recommended. Using ImGuiListClipper requires
            // - A) random access into your data
            // - B) items all being the  same height,
            // both of which we can handle since we have an array pointing to the beginning of each line of text.
            // When using the filter (in the block of code above) we don't have random access into the data to display
            // anymore, which is why we don't use the clipper. Storing or skimming through the search result would make
            // it possible (and would be recommended if you want to search through tens of thousands of entries).
            ImGuiListClipper clipper;
            clipper.Begin(mLineOffsets.Size);
            while (clipper.Step())
            {
                for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
                {
                    const char *line_start = buf + mLineOffsets[line_no];
                    const char *line_end = (line_no + 1 < mLineOffsets.Size) ? (buf + mLineOffsets[line_no + 1] - 1) : buf_end;
                    ImGui::TextUnformatted(line_start, line_end);
                }
            }
            clipper.End();
        }
        ImGui::PopStyleVar();

        // Keep up at the bottom of the scroll region if we were already at the bottom at the beginning of the frame.
        // Using a scrollbar or mouse-wheel will take away from the bottom edge.
        if (mAutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        {
            ImGui::SetScrollHereY(1.0f);
        }
    }

    ImGui::EndChild();
    ImGui::End();
}

}